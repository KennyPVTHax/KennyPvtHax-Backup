#pragma once
#include "KennyCharacters.h"
#include <cerrno>
#ifdef __ANDROID__
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include "KennyGLUpload.h"
#include <android/asset_manager.h>
namespace KennyCharacters {
// Copy an optional offline APK pack into app-private storage once. Existing
// user files are preserved. APK paths are validated; no runtime network access.
inline bool APKRead(AAssetManager* manager,const std::string& path,size_t limit,std::vector<uint8_t>& bytes){
    bytes.clear();if(!manager||!KennyAssets::Path(path))return false;
    AAsset* asset=AAssetManager_open(manager,path.c_str(),AASSET_MODE_BUFFER);if(!asset)return false;
    const auto size=AAsset_getLength(asset);bool ok=size>0&&size_t(size)<=limit;
    if(ok){bytes.resize(size_t(size));size_t n=0;while(n<bytes.size()){int read=AAsset_read(asset,bytes.data()+n,bytes.size()-n);if(read<=0){ok=false;break;}n+=size_t(read);}}
    AAsset_close(asset);if(!ok)bytes.clear();return ok;
}
inline int PrivateDirectory(int parent,const char* name){
    if(mkdirat(parent,name,0700)!=0&&errno!=EEXIST)return -1;
    return openat(parent,name,O_RDONLY|O_DIRECTORY|O_NOFOLLOW|O_CLOEXEC);
}
inline void StageFile(int directory,const std::string& path,const std::vector<uint8_t>& bytes){
    if(!KennyAssets::Path(path)||bytes.empty())return;
    int fd=dup(directory);size_t start=0;
    while(fd>=0){auto slash=path.find('/',start);if(slash==std::string::npos)break;
        auto part=path.substr(start,slash-start);int next=PrivateDirectory(fd,part.c_str());close(fd);fd=next;start=slash+1;}
    if(fd<0)return;
    const std::string file=path.substr(start);int existing=openat(fd,file.c_str(),O_RDONLY|O_NONBLOCK|O_NOFOLLOW|O_CLOEXEC);
    if(existing>=0){close(existing);close(fd);return;}
    // Exclusive staging; detected incomplete writes are removed. Runtime
    // registry validation rejects any pre-existing malformed file safely.
    int out=openat(fd,file.c_str(),O_WRONLY|O_CREAT|O_EXCL|O_NOFOLLOW|O_CLOEXEC,0600);
    if(out>=0){size_t n=0;while(n<bytes.size()){ssize_t done=write(out,bytes.data()+n,bytes.size()-n);if(done<=0)break;n+=size_t(done);}bool ok=n==bytes.size()&&fsync(out)==0;close(out);if(!ok)unlinkat(fd,file.c_str(),0);}
    close(fd);
}
inline bool StageAPK(AAssetManager* manager,const char* directory){
    std::vector<uint8_t> bytes;nlohmann::json index;
    if(!directory||!APKRead(manager,"anime/index.json",32768,bytes)||!Registry::JSON(bytes,index))return false;
    auto packs=index.find("characters");if(packs==index.end()||!packs->is_array()||packs->size()>8)return false;
    int activity=open(directory,O_RDONLY|O_DIRECTORY|O_NOFOLLOW|O_CLOEXEC);if(activity<0)return false;
    int assets=PrivateDirectory(activity,"assets");close(activity);if(assets<0)return false;
    int root=PrivateDirectory(assets,"anime");close(assets);if(root<0)return false;
    size_t copied=0;
    for(const auto& value:*packs){if(!value.is_string())continue;auto id=value.get<std::string>();if(!KennyAssets::Token(id))continue;
        const std::string prefix="anime/"+id+"/";nlohmann::json manifest;
        if(!APKRead(manager,prefix+"manifest.json",32768,bytes)||!Registry::JSON(bytes,manifest)||Registry::Text(manifest,"id")!=id)continue;
        int target=PrivateDirectory(root,id.c_str());if(target<0)continue;StageFile(target,"manifest.json",bytes);
        auto copy=[&](const std::string& file,size_t limit,const char* extension){if(file.size()>=4&&file.substr(file.size()-4)==extension&&KennyAssets::Path(file)&&APKRead(manager,prefix+file,limit,bytes)&&copied+bytes.size()<=32*1024*1024){copied+=bytes.size();StageFile(target,file,bytes);}};
        copy(Registry::Text(manifest,"artwork","character.png"),8*1024*1024,".png");copy(Registry::Text(manifest,"launcher","launcher.png"),8*1024*1024,".png");
        auto voices=manifest.find("voice_packs");if(voices!=manifest.end()&&voices->is_array()&&voices->size()<=4)for(const auto& pack:*voices){
            if(!pack.is_object())continue;auto events=pack.find("events");if(events==pack.end()||!events->is_object())continue;
            for(const char* name:EventNames){auto files=events->find(name);if(files==events->end()||!files->is_array()||files->size()>3)continue;for(const auto& file:*files)if(file.is_string())copy(file.get<std::string>(),1048576,".wav");}
        }close(target);
    }close(root);return true;
}
inline KennyThemeBackground::ArtworkFrame UploadGL(void*,const KennyAssets::Image& image){
    if(eglGetCurrentContext()==EGL_NO_CONTEXT)return {};
    GLint limit=0;glGetIntegerv(GL_MAX_TEXTURE_SIZE,&limit);
    if(limit<=0||!image.width||!image.height||image.width>unsigned(limit)||image.height>unsigned(limit)||image.rgba.size()!=size_t(image.width)*image.height*4)return {};
    const GLuint id=KennyGL::UploadRGBA(image.rgba.data(),int(image.width),int(image.height),true,true);
    if(!id)return {};
    return {reinterpret_cast<ImTextureID>(uintptr_t(id)),int(image.width),int(image.height)};
}
inline void ReleaseGL(void*,KennyThemeBackground::ArtworkFrame frame){GLuint id=GLuint(reinterpret_cast<uintptr_t>(frame.texture));if(id)glDeleteTextures(1,&id);}
}
#endif
