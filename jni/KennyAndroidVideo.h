#pragma once
#include "KennyPresentationMedia.h"
#include "KennyCharacterGL.h"
#include "KennyDiagnostics.h"
#ifdef __ANDROID__
#include <android/native_activity.h>
#include <android/native_window_jni.h>
#include <media/NdkMediaCodec.h>
#include <media/NdkMediaExtractor.h>
#include <GLES2/gl2ext.h>
#include <jni.h>
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <thread>

namespace KennyPresentation {
inline bool StageAPK(AAssetManager* manager,const char* privatePath){
    std::vector<uint8_t> bytes;nlohmann::json manifest;
    if(!manager||!privatePath||!KennyCharacters::APKRead(manager,"presentation/manifest.json",32768,bytes)||!KennyCharacters::Registry::JSON(bytes,manifest))return false;
    auto schema=manifest.find("schema");if(schema==manifest.end()||!schema->is_number_integer()||*schema!=1||
        KennyCharacters::Registry::Text(manifest,"logo")!="launcher.png"||KennyCharacters::Registry::Text(manifest,"video")!="anime-background.mp4"||KennyCharacters::Registry::Text(manifest,"fallback")!="anime-fallback.png")return false;
    int base=open(privatePath,O_RDONLY|O_DIRECTORY|O_NOFOLLOW|O_CLOEXEC);if(base<0)return false;
    int assets=KennyCharacters::PrivateDirectory(base,"assets");close(base);if(assets<0)return false;
    int target=KennyCharacters::PrivateDirectory(assets,"presentation");close(assets);if(target<0)return false;
    KennyCharacters::StageFile(target,"manifest.json",bytes);
    for(const char* name:{"launcher.png","anime-fallback.png","anime-background.mp4"}){
        if(KennyCharacters::APKRead(manager,std::string("presentation/")+name,std::strcmp(name,"anime-background.mp4")==0?VideoLimit:8u*1024u*1024u,bytes))KennyCharacters::StageFile(target,name,bytes);
    }close(target);return true;
}
inline KennyThemeBackground::ArtworkFrame UploadImage(void* user,const KennyAssets::Image& image){
    const auto frame=KennyCharacters::UploadGL(user,image);if(!frame.Valid())return {};
    GLint binding=0;glGetIntegerv(GL_TEXTURE_BINDING_2D,&binding);
    glBindTexture(GL_TEXTURE_2D,GLuint(reinterpret_cast<uintptr_t>(frame.texture)));
    glGenerateMipmap(GL_TEXTURE_2D);glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glBindTexture(GL_TEXTURE_2D,GLuint(binding));return frame;
}
enum class VideoStatus {Idle,Opening,Playing,Paused,Missing,Unsupported,JNIError,GLFailed,DecodeFailed,FrameFailed};
inline const char* StatusText(VideoStatus status){switch(status){
case VideoStatus::Playing:return "Decoded Android video frame submitted; audio muted. Verify on your device.";
case VideoStatus::Paused:return "Video paused while hidden, inactive, off or Reduced motion.";
case VideoStatus::Opening:return "Opening optional Android video decoder.";
case VideoStatus::Missing:return "Private video pack missing; install into the owning host and restart.";
case VideoStatus::Unsupported:return "Video format unavailable on this device; still fallback active.";
case VideoStatus::JNIError:return "Android video surface unavailable; still fallback active.";
case VideoStatus::GLFailed:return "Video texture conversion unavailable; still fallback active.";
case VideoStatus::DecodeFailed:return "Optional decoder failed; still fallback active.";
case VideoStatus::FrameFailed:return "Video surface frame failed; still fallback active.";
default:return "Video waits until Anime is visible; audio remains muted.";}}
struct ThreadEnvironment {
    JavaVM* vm=nullptr;JNIEnv* env=nullptr;bool attached=false;
    ~ThreadEnvironment(){if(attached&&vm)vm->DetachCurrentThread();}
    JNIEnv* Get(JavaVM* value){
        if(vm==value&&env)return env;
        if(attached&&vm)vm->DetachCurrentThread();vm=value;env=nullptr;attached=false;
        if(!vm)return nullptr;
        auto result=vm->GetEnv(reinterpret_cast<void**>(&env),JNI_VERSION_1_6);
        if(result==JNI_EDETACHED){attached=vm->AttachCurrentThread(&env,nullptr)==JNI_OK;if(!attached)env=nullptr;}
        else if(result!=JNI_OK)env=nullptr;
        return env;
    }
};
struct Environment {
    JNIEnv* env=nullptr;JNIEnv* raw=nullptr;
    explicit Environment(JavaVM* value){static thread_local ThreadEnvironment thread;raw=thread.Get(value);env=raw&&!raw->ExceptionCheck()?raw:nullptr;}
    bool Check(){if(!env)return false;if(env->ExceptionCheck()){env->ExceptionClear();return false;}return true;}
};
// Owns optional video resources only. All GL/JNI consumer calls are performed on
// the existing renderer thread/context; decoder work has one bounded worker.
struct AndroidBackend {
    Assets assets;
    JavaVM* vm=nullptr;EGLContext owner=EGL_NO_CONTEXT;
    jobject surfaceTexture=nullptr,surface=nullptr;jfloatArray transform=nullptr;
    jmethodID update=nullptr,matrix=nullptr,timestamp=nullptr,releaseTexture=nullptr,releaseSurface=nullptr;
    ANativeWindow* window=nullptr;
    GLuint external=0,target=0,fbo=0,program=0,vbo=0,vao=0;
    GLint matrixUniform=-1;int width=0,height=0;
    std::thread worker;std::mutex mutex;std::condition_variable wake;
    std::atomic<bool> stopping{false},playing{false},pending{false},broken{false};
    std::atomic<VideoStatus> status{VideoStatus::Idle};
    std::atomic<uint64_t> frames{0},loops{0},dropped{0};
    std::atomic<int64_t> heartbeat{0};
    static int64_t Now(){return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();}
    bool attempted=false,hasFrame=false,logoReported=false;int64_t lastTimestamp=-1;VideoStatus reported=VideoStatus::Idle;
    ~AndroidBackend(){Clear(eglGetCurrentContext()==EGL_NO_CONTEXT||eglGetCurrentContext()!=owner);}
    const char* Status()const{return assets.video<0?assets.status:StatusText(status.load());}
    void Stop(){stopping.store(true);playing.store(false);wake.notify_all();if(worker.joinable())worker.join();pending.store(false);}
    void ReleaseJava(Environment& e){
        if(e.env){if(surface&&releaseSurface){e.env->CallVoidMethod(surface,releaseSurface);e.Check();}if(surfaceTexture&&releaseTexture){e.env->CallVoidMethod(surfaceTexture,releaseTexture);e.Check();}
        }
        if(e.raw){if(surface)e.raw->DeleteGlobalRef(surface);if(surfaceTexture)e.raw->DeleteGlobalRef(surfaceTexture);if(transform)e.raw->DeleteGlobalRef(transform);}
        surface=nullptr;surfaceTexture=nullptr;transform=nullptr;
        if(window)ANativeWindow_release(window);window=nullptr;
    }
    void ReleaseVideo(bool lost){
        Stop();Environment e(vm);ReleaseJava(e);
        if(!lost){if(external)glDeleteTextures(1,&external);if(target)glDeleteTextures(1,&target);if(fbo)glDeleteFramebuffers(1,&fbo);if(vbo)glDeleteBuffers(1,&vbo);if(vao)glDeleteVertexArrays(1,&vao);if(program)glDeleteProgram(program);}
        external=target=fbo=vbo=vao=program=0;hasFrame=false;attempted=false;lastTimestamp=-1;
        status.store(VideoStatus::Idle);broken.store(false);
    }
    void Clear(bool lost){ReleaseVideo(lost);assets.ClearTextures(lost);owner=EGL_NO_CONTEXT;logoReported=false;}
    bool Fail(VideoStatus reason){ReleaseVideo(false);attempted=true;status.store(reason);return false;}
    static GLuint Shader(GLenum type,const char* text){GLuint shader=glCreateShader(type);if(!shader)return 0;glShaderSource(shader,1,&text,nullptr);glCompileShader(shader);GLint okay=0;glGetShaderiv(shader,GL_COMPILE_STATUS,&okay);if(!okay){glDeleteShader(shader);return 0;}return shader;}
    struct GLState {
        GLint active=0,tex2d=0,texExternal=0,program=0,array=0,vao=0,draw=0,read=0,viewport[4]{};
        GLboolean blend=false,depth=false,stencil=false,scissor=false,cull=false,discard=false,mask[4]{};
        GLState(){glGetIntegerv(GL_ACTIVE_TEXTURE,&active);glActiveTexture(GL_TEXTURE0);glGetIntegerv(GL_TEXTURE_BINDING_2D,&tex2d);glGetIntegerv(GL_TEXTURE_BINDING_EXTERNAL_OES,&texExternal);glGetIntegerv(GL_CURRENT_PROGRAM,&program);glGetIntegerv(GL_ARRAY_BUFFER_BINDING,&array);glGetIntegerv(GL_VERTEX_ARRAY_BINDING,&vao);glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING,&draw);glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING,&read);glGetIntegerv(GL_VIEWPORT,viewport);glGetBooleanv(GL_COLOR_WRITEMASK,mask);blend=glIsEnabled(GL_BLEND);depth=glIsEnabled(GL_DEPTH_TEST);stencil=glIsEnabled(GL_STENCIL_TEST);scissor=glIsEnabled(GL_SCISSOR_TEST);cull=glIsEnabled(GL_CULL_FACE);discard=glIsEnabled(GL_RASTERIZER_DISCARD);}
        ~GLState(){glUseProgram(program);glBindVertexArray(vao);glBindBuffer(GL_ARRAY_BUFFER,array);glBindFramebuffer(GL_DRAW_FRAMEBUFFER,draw);glBindFramebuffer(GL_READ_FRAMEBUFFER,read);glViewport(viewport[0],viewport[1],viewport[2],viewport[3]);glColorMask(mask[0],mask[1],mask[2],mask[3]);for(auto p:{std::pair<GLenum,GLboolean>(GL_BLEND,blend),{GL_DEPTH_TEST,depth},{GL_STENCIL_TEST,stencil},{GL_SCISSOR_TEST,scissor},{GL_CULL_FACE,cull},{GL_RASTERIZER_DISCARD,discard}}){if(p.second)glEnable(p.first);else glDisable(p.first);}glActiveTexture(GL_TEXTURE0);glBindTexture(GL_TEXTURE_2D,tex2d);glBindTexture(GL_TEXTURE_EXTERNAL_OES,texExternal);glActiveTexture(active);}
    };
    bool Graphics(){
        GLState saved;
        const char* vertex="attribute vec2 pos;varying vec2 uv;uniform mat4 transform;void main(){gl_Position=vec4(pos,0.,1.);uv=(transform*vec4((pos.x+1.)*.5,(1.-pos.y)*.5,0.,1.)).xy;}";
        const char* fragment="#extension GL_OES_EGL_image_external : require\nprecision mediump float;varying vec2 uv;uniform samplerExternalOES movie;void main(){gl_FragColor=texture2D(movie,uv);}";
        GLuint vs=Shader(GL_VERTEX_SHADER,vertex),fs=Shader(GL_FRAGMENT_SHADER,fragment);
        if(!vs||!fs){if(vs)glDeleteShader(vs);if(fs)glDeleteShader(fs);return false;}
        program=glCreateProgram();glAttachShader(program,vs);glAttachShader(program,fs);glBindAttribLocation(program,0,"pos");glLinkProgram(program);glDeleteShader(vs);glDeleteShader(fs);GLint okay=0;glGetProgramiv(program,GL_LINK_STATUS,&okay);if(!okay)return false;
        matrixUniform=glGetUniformLocation(program,"transform");glUseProgram(program);glUniform1i(glGetUniformLocation(program,"movie"),0);
        glGenTextures(1,&target);glBindTexture(GL_TEXTURE_2D,target);glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,nullptr);
        glGenFramebuffers(1,&fbo);glBindFramebuffer(GL_FRAMEBUFFER,fbo);glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,target,0);if(glCheckFramebufferStatus(GL_FRAMEBUFFER)!=GL_FRAMEBUFFER_COMPLETE)return false;
        constexpr float quad[]={-1,-1,1,-1,-1,1,1,1};glGenVertexArrays(1,&vao);glBindVertexArray(vao);glGenBuffers(1,&vbo);glBindBuffer(GL_ARRAY_BUFFER,vbo);glBufferData(GL_ARRAY_BUFFER,sizeof(quad),quad,GL_STATIC_DRAW);glEnableVertexAttribArray(0);glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,2*sizeof(float),nullptr);
        return external&&target&&fbo&&vao&&vbo&&program&&matrixUniform>=0;
    }
    bool Surface(JNIEnv* env){
        GLState saved;glGenTextures(1,&external);glBindTexture(GL_TEXTURE_EXTERNAL_OES,external);glTexParameteri(GL_TEXTURE_EXTERNAL_OES,GL_TEXTURE_MIN_FILTER,GL_LINEAR);glTexParameteri(GL_TEXTURE_EXTERNAL_OES,GL_TEXTURE_MAG_FILTER,GL_LINEAR);glTexParameteri(GL_TEXTURE_EXTERNAL_OES,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);glTexParameteri(GL_TEXTURE_EXTERNAL_OES,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
        auto klass=env->FindClass("android/graphics/SurfaceTexture");if(!klass)return false;
        auto ctor=env->GetMethodID(klass,"<init>","(I)V");auto size=env->GetMethodID(klass,"setDefaultBufferSize","(II)V");
        update=env->GetMethodID(klass,"updateTexImage","()V");matrix=env->GetMethodID(klass,"getTransformMatrix","([F)V");timestamp=env->GetMethodID(klass,"getTimestamp","()J");releaseTexture=env->GetMethodID(klass,"release","()V");
        if(!ctor||!size||!update||!matrix||!timestamp||!releaseTexture){env->DeleteLocalRef(klass);return false;}
        jobject local=env->NewObject(klass,ctor,jint(external));env->DeleteLocalRef(klass);if(!local)return false;
        surfaceTexture=env->NewGlobalRef(local);env->DeleteLocalRef(local);if(!surfaceTexture)return false;env->CallVoidMethod(surfaceTexture,size,width,height);if(env->ExceptionCheck())return false;
        auto surfaceClass=env->FindClass("android/view/Surface");if(!surfaceClass)return false;
        auto surfaceCtor=env->GetMethodID(surfaceClass,"<init>","(Landroid/graphics/SurfaceTexture;)V");releaseSurface=env->GetMethodID(surfaceClass,"release","()V");if(!surfaceCtor||!releaseSurface){env->DeleteLocalRef(surfaceClass);return false;}
        local=env->NewObject(surfaceClass,surfaceCtor,surfaceTexture);env->DeleteLocalRef(surfaceClass);if(!local)return false;surface=env->NewGlobalRef(local);env->DeleteLocalRef(local);if(!surface)return false;
        window=ANativeWindow_fromSurface(env,surface);auto array=env->NewFloatArray(16);if(array){transform=static_cast<jfloatArray>(env->NewGlobalRef(array));env->DeleteLocalRef(array);}return window&&transform;
    }
    void Decode(){
        AMediaExtractor* extractor=AMediaExtractor_new();AMediaCodec* codec=nullptr;AMediaFormat* format=nullptr;
        struct stat st{};bool okay=extractor&&fstat(assets.video,&st)==0&&AMediaExtractor_setDataSourceFd(extractor,assets.video,0,st.st_size)==AMEDIA_OK;
        if(okay){const size_t tracks=AMediaExtractor_getTrackCount(extractor);okay=false;for(size_t i=0;i<tracks&&i<16;++i){auto f=AMediaExtractor_getTrackFormat(extractor,i);const char* mime=nullptr;
            if(f&&AMediaFormat_getString(f,AMEDIAFORMAT_KEY_MIME,&mime)&&mime&&std::strncmp(mime,"video/",6)==0){format=f;codec=AMediaCodec_createDecoderByType(mime);okay=codec&&AMediaExtractor_selectTrack(extractor,i)==AMEDIA_OK;break;}if(f)AMediaFormat_delete(f);}}
        if(okay)okay=AMediaCodec_configure(codec,format,window,nullptr,0)==AMEDIA_OK&&AMediaCodec_start(codec)==AMEDIA_OK;
        if(format)AMediaFormat_delete(format);
        if(!okay){status.store(VideoStatus::DecodeFailed);broken.store(true);}
        bool eos=false;Clock clock;
        while(okay&&!stopping.load()){
            if(!playing.load()){
                clock.Pause();std::unique_lock<std::mutex> lock(mutex);wake.wait(lock,[&]{return stopping.load()||playing.load();});continue;
            }
            if(pending.load()){
                std::unique_lock<std::mutex> lock(mutex);
                const bool consumed=wake.wait_for(lock,std::chrono::seconds(2),[&]{return stopping.load()||!playing.load()||!pending.load();});
                if(!consumed){
                    if(Now()-heartbeat.load()>1000000){playing.store(false);clock.Pause();status.store(VideoStatus::Paused);continue;}
                    status.store(VideoStatus::FrameFailed);broken.store(true);okay=false;break;
                }
                continue;
            }
            if(!eos){const ssize_t input=AMediaCodec_dequeueInputBuffer(codec,1000);if(input>=0){size_t capacity=0;auto data=AMediaCodec_getInputBuffer(codec,size_t(input),&capacity);
                if(!data||!capacity){okay=false;break;}
                const ssize_t count=AMediaExtractor_readSampleData(extractor,data,capacity);const int64_t pts=AMediaExtractor_getSampleTime(extractor);
                if(count<0){eos=true;okay=AMediaCodec_queueInputBuffer(codec,size_t(input),0,0,0,AMEDIACODEC_BUFFER_FLAG_END_OF_STREAM)==AMEDIA_OK;}
                else if(size_t(count)>capacity||pts<0){okay=false;break;}
                else {okay=AMediaCodec_queueInputBuffer(codec,size_t(input),0,size_t(count),uint64_t(pts)+1000,0)==AMEDIA_OK;AMediaExtractor_advance(extractor);}
            }}
            AMediaCodecBufferInfo info{};const ssize_t output=AMediaCodec_dequeueOutputBuffer(codec,&info,1000);
            if(output>=0){
                if(info.flags&AMEDIACODEC_BUFFER_FLAG_END_OF_STREAM){AMediaCodec_releaseOutputBuffer(codec,size_t(output),false);okay=AMediaExtractor_seekTo(extractor,0,AMEDIAEXTRACTOR_SEEK_CLOSEST_SYNC)==AMEDIA_OK&&AMediaCodec_flush(codec)==AMEDIA_OK;eos=false;clock.Pause();++loops;continue;}
                if(info.flags&AMEDIACODEC_BUFFER_FLAG_CODEC_CONFIG){AMediaCodec_releaseOutputBuffer(codec,size_t(output),false);continue;}
                const auto due=clock.Due(info.presentationTimeUs,std::chrono::steady_clock::now());
                {std::unique_lock<std::mutex> lock(mutex);wake.wait_until(lock,due,[&]{return stopping.load()||!playing.load();});}
                if(stopping.load()||!playing.load()){AMediaCodec_releaseOutputBuffer(codec,size_t(output),false);clock.Pause();continue;}
                if(std::chrono::steady_clock::now()-due>std::chrono::milliseconds(100)){
                    AMediaCodec_releaseOutputBuffer(codec,size_t(output),false);++dropped;continue;
                }
                // One outstanding SurfaceTexture frame. Publish before release
                // so the consumer never observes a frame without ownership.
                pending.store(true);
                if(AMediaCodec_releaseOutputBuffer(codec,size_t(output),true)!=AMEDIA_OK){pending.store(false);okay=false;}
            }else if(output==AMEDIACODEC_INFO_OUTPUT_FORMAT_CHANGED){auto changed=AMediaCodec_getOutputFormat(codec);int32_t w=0,h=0;
                if(changed&&AMediaFormat_getInt32(changed,AMEDIAFORMAT_KEY_WIDTH,&w)&&AMediaFormat_getInt32(changed,AMEDIAFORMAT_KEY_HEIGHT,&h)&&
                   (w<=0||h<=0||w>4096||h>4096||uint64_t(w)*h>2097152))okay=false;
                if(changed)AMediaFormat_delete(changed);
            }
            else if(output!=AMEDIACODEC_INFO_TRY_AGAIN_LATER&&output!=AMEDIACODEC_INFO_OUTPUT_BUFFERS_CHANGED){okay=false;}
        }
        if(!okay&&!stopping.load()){if(!broken.load())status.store(VideoStatus::DecodeFailed);broken.store(true);}
        if(codec){AMediaCodec_stop(codec);AMediaCodec_delete(codec);}if(extractor)AMediaExtractor_delete(extractor);
    }
    bool Open(ANativeActivity* activity){
        attempted=true;status.store(VideoStatus::Opening);if(!activity||!activity->vm||assets.video<0)return Fail(VideoStatus::JNIError);vm=activity->vm;
        AMediaExtractor* extractor=AMediaExtractor_new();struct stat st{};AMediaFormat* selected=nullptr;
        bool okay=extractor&&fstat(assets.video,&st)==0&&AMediaExtractor_setDataSourceFd(extractor,assets.video,0,st.st_size)==AMEDIA_OK;
        if(okay)for(size_t i=0;i<AMediaExtractor_getTrackCount(extractor)&&i<16;++i){auto format=AMediaExtractor_getTrackFormat(extractor,i);const char* mime=nullptr;
            if(format&&AMediaFormat_getString(format,AMEDIAFORMAT_KEY_MIME,&mime)&&mime&&!std::strcmp(mime,"video/avc")){selected=format;break;}if(format)AMediaFormat_delete(format);}
        okay=selected&&AMediaFormat_getInt32(selected,AMEDIAFORMAT_KEY_WIDTH,&width)&&AMediaFormat_getInt32(selected,AMEDIAFORMAT_KEY_HEIGHT,&height)&&width>0&&height>0&&width<=4096&&height<=4096&&uint64_t(width)*height<=2097152;
        if(selected)AMediaFormat_delete(selected);if(extractor)AMediaExtractor_delete(extractor);
        if(!okay)return Fail(VideoStatus::Unsupported);
        bool extension=false;GLint count=0;glGetIntegerv(GL_NUM_EXTENSIONS,&count);
        for(GLint i=0;i<count&&i<4096;++i){const auto name=glGetStringi(GL_EXTENSIONS,GLuint(i));if(name&&!std::strcmp(reinterpret_cast<const char*>(name),"GL_OES_EGL_image_external")){extension=true;break;}}
        if(!extension)return Fail(VideoStatus::Unsupported);
        Environment e(vm);if(!e.env||!Surface(e.env)||!e.Check()){e.Check();return Fail(VideoStatus::JNIError);}
        if(!Graphics())return Fail(VideoStatus::GLFailed);
        stopping.store(false);broken.store(false);playing.store(true);
        try{worker=std::thread([this]{Decode();});}catch(const std::system_error&){return Fail(VideoStatus::DecodeFailed);}
        return true;
    }
    void Consume(){
        if(!pending.load()||broken.load())return;
        Environment e(vm);if(!e.env){broken.store(true);status.store(VideoStatus::JNIError);return;}
        GLState saved;e.env->CallVoidMethod(surfaceTexture,update);if(!e.Check()){broken.store(true);status.store(VideoStatus::FrameFailed);return;}
        const auto stamp=e.env->CallLongMethod(surfaceTexture,timestamp);if(!e.Check()){broken.store(true);status.store(VideoStatus::FrameFailed);return;}
        if(stamp<=0||stamp==lastTimestamp)return; // Buffer may not have arrived yet.
        e.env->CallVoidMethod(surfaceTexture,matrix,transform);float values[16]{};if(!e.Check()){broken.store(true);status.store(VideoStatus::FrameFailed);return;}
        e.env->GetFloatArrayRegion(transform,0,16,values);if(!e.Check()){broken.store(true);status.store(VideoStatus::FrameFailed);return;}
        for(float v:values)if(!std::isfinite(v)){broken.store(true);status.store(VideoStatus::FrameFailed);return;}
        glBindFramebuffer(GL_FRAMEBUFFER,fbo);glViewport(0,0,width,height);glDisable(GL_BLEND);glDisable(GL_DEPTH_TEST);glDisable(GL_STENCIL_TEST);glDisable(GL_SCISSOR_TEST);glDisable(GL_CULL_FACE);glDisable(GL_RASTERIZER_DISCARD);glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
        glUseProgram(program);glBindVertexArray(vao);glActiveTexture(GL_TEXTURE0);glBindTexture(GL_TEXTURE_EXTERNAL_OES,external);glUniformMatrix4fv(matrixUniform,1,GL_FALSE,values);glDrawArrays(GL_TRIANGLE_STRIP,0,4);
        hasFrame=true;lastTimestamp=stamp;++frames;pending.store(false);wake.notify_all();status.store(VideoStatus::Playing);
    }
    KennyThemeBackground::ArtworkFrame Pump(ANativeActivity* activity,bool visible,bool motion){
        heartbeat.store(Now());owner=eglGetCurrentContext();
        assets.upload=UploadImage;assets.release=KennyCharacters::ReleaseGL;assets.Prepare(visible);
        if(assets.logoAttempted&&!logoReported){logoReported=true;
            KennyDiagnostics::Event(42,assets.logoTexture.Valid()?KennyDiagnostics::Severity::Info:KennyDiagnostics::Severity::Warning,0,assets.logoTexture.Valid(),
                assets.logoTexture.Valid()?"Custom launcher photo texture ready":"Custom launcher photo missing/invalid/unavailable; K fallback active");
        }
        const bool want=visible&&motion;
        if(want&&assets.video>=0&&!attempted)Open(activity);
        if(worker.joinable()){
            if(playing.exchange(want)!=want)wake.notify_all();
            if(want&&!broken.load())Consume();
            if(!want&&!broken.load())status.store(VideoStatus::Paused);
        }
        if(broken.load()){playing.store(false);wake.notify_all();}
        const auto now=status.load();if(now!=reported){reported=now;
            KennyDiagnostics::Event(41,broken.load()?KennyDiagnostics::Severity::Warning:KennyDiagnostics::Severity::Info,0,!broken.load(),"Optional Anime video: %s",StatusText(now));
        }
        if(hasFrame&&!broken.load())return {reinterpret_cast<ImTextureID>(uintptr_t(target)),width,height};
        return assets.posterTexture;
    }
};
} // namespace KennyPresentation
#endif
