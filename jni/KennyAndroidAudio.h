#pragma once
#include "KennyAudio.h"
#ifdef __ANDROID__
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#endif

namespace KennyAudio {
// Owns only this UI's PCM player/output mix; no focus requests, media volume
// changes or access to the background application's sound resources.
class AndroidBackend {
    Bank bank;
    Mixer mixer;
    bool attempted=false,ready=false;
    const char* status="UI audio unavailable in this host preview.";
#ifdef __ANDROID__
    SLObjectItf engineObject=nullptr,mixObject=nullptr,playerObject=nullptr;
    SLEngineItf engine=nullptr;
    SLPlayItf play=nullptr;
    SLAndroidSimpleBufferQueueItf buffers=nullptr;
    std::array<std::array<int16_t,256>,2> pcm{};
    std::atomic<bool> running{false},playing{false};
    unsigned slot=0,idleSamples=0;
    static void Callback(SLAndroidSimpleBufferQueueItf queue,void* context) {
        auto& self=*static_cast<AndroidBackend*>(context);
        if(!self.running.load(std::memory_order_acquire))return;
        auto& block=self.pcm[self.slot];self.slot=(self.slot+1)%2;
        self.mixer.Render(block.data(),block.size());
        bool active=self.mixer.character!=nullptr;for(const auto& voice:self.mixer.voices)active|=voice.clip!=nullptr;
        active|=self.mixer.read.load(std::memory_order_acquire)!=self.mixer.write.load(std::memory_order_acquire);
        self.idleSamples=active ? 0:self.idleSamples+block.size();
        if(self.idleSamples>=SampleRate/8) {
            (*self.play)->SetPlayState(self.play,SL_PLAYSTATE_STOPPED);
            self.playing.store(false,std::memory_order_release);return;
        }
        if((*queue)->Enqueue(queue,block.data(),block.size()*sizeof(int16_t))!=SL_RESULT_SUCCESS) {
            (*self.play)->SetPlayState(self.play,SL_PLAYSTATE_STOPPED);
            self.playing.store(false,std::memory_order_release);
        }
    }
#endif
public:
    Dispatcher dispatcher;
    AndroidBackend()=default;
    AndroidBackend(const AndroidBackend&)=delete;
    AndroidBackend& operator=(const AndroidBackend&)=delete;
    ~AndroidBackend(){Shutdown();}
    bool Initialize() {
        if(attempted)return ready;
        attempted=true;
#ifdef __ANDROID__
        bank.Initialize();mixer.bank=&bank;
        if(slCreateEngine(&engineObject,0,nullptr,0,nullptr,nullptr)!=SL_RESULT_SUCCESS) return Fail();
        if((*engineObject)->Realize(engineObject,SL_BOOLEAN_FALSE)!=SL_RESULT_SUCCESS ||
           (*engineObject)->GetInterface(engineObject,SL_IID_ENGINE,&engine)!=SL_RESULT_SUCCESS) return Fail();
        if((*engine)->CreateOutputMix(engine,&mixObject,0,nullptr,nullptr)!=SL_RESULT_SUCCESS ||
           (*mixObject)->Realize(mixObject,SL_BOOLEAN_FALSE)!=SL_RESULT_SUCCESS) return Fail();
        SLDataLocator_AndroidSimpleBufferQueue locator={SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE,2};
        SLDataFormat_PCM format={SL_DATAFORMAT_PCM,1,SL_SAMPLINGRATE_48,SL_PCMSAMPLEFORMAT_FIXED_16,
                                SL_PCMSAMPLEFORMAT_FIXED_16,SL_SPEAKER_FRONT_CENTER,SL_BYTEORDER_LITTLEENDIAN};
        SLDataSource source={&locator,&format};
        SLDataLocator_OutputMix output={SL_DATALOCATOR_OUTPUTMIX,mixObject};SLDataSink sink={&output,nullptr};
        const SLInterfaceID ids[]={SL_IID_ANDROIDSIMPLEBUFFERQUEUE};const SLboolean required[]={SL_BOOLEAN_TRUE};
        if((*engine)->CreateAudioPlayer(engine,&playerObject,&source,&sink,1,ids,required)!=SL_RESULT_SUCCESS ||
           (*playerObject)->Realize(playerObject,SL_BOOLEAN_FALSE)!=SL_RESULT_SUCCESS ||
           (*playerObject)->GetInterface(playerObject,SL_IID_PLAY,&play)!=SL_RESULT_SUCCESS ||
           (*playerObject)->GetInterface(playerObject,SL_IID_ANDROIDSIMPLEBUFFERQUEUE,&buffers)!=SL_RESULT_SUCCESS ||
           (*buffers)->RegisterCallback(buffers,Callback,this)!=SL_RESULT_SUCCESS) return Fail();
        running.store(true,std::memory_order_release);ready=true;
        dispatcher.mixer=&mixer;status="UI sound profiles are ready.";
#endif
        return ready;
    }
    const char* Status() const{return status;}
    bool Ready() const{return ready;}
    void Pump(const KennyAppearance::Preferences& p) {
        dispatcher.Refresh(p);
#ifdef __ANDROID__
        // Audio stops its player after a short silent tail. A tap reuses the
        // existing objects/buffers; it never creates/loads a resource.
        if(!ready || playing.load(std::memory_order_acquire) ||
           mixer.read.load(std::memory_order_acquire)==mixer.write.load(std::memory_order_acquire))return;
        (*buffers)->Clear(buffers);idleSamples=0;slot=0;
        for(auto& block:pcm) {
            mixer.Render(block.data(),block.size());
            if((*buffers)->Enqueue(buffers,block.data(),block.size()*sizeof(int16_t))!=SL_RESULT_SUCCESS){Fail();return;}
        }
        playing.store(true,std::memory_order_release);
        if((*play)->SetPlayState(play,SL_PLAYSTATE_PLAYING)!=SL_RESULT_SUCCESS)Fail();
#endif
    }
    void Shutdown() {
        dispatcher.mixer=nullptr;ready=false;
#ifdef __ANDROID__
        running.store(false,std::memory_order_release);
        if(play)(*play)->SetPlayState(play,SL_PLAYSTATE_STOPPED);
        // Destroy the player before engine/data: OpenSL retires its callbacks.
        if(playerObject)(*playerObject)->Destroy(playerObject);
        playerObject=nullptr;play=nullptr;buffers=nullptr;
        if(mixObject)(*mixObject)->Destroy(mixObject);
        mixObject=nullptr;
        if(engineObject)(*engineObject)->Destroy(engineObject);
        engineObject=nullptr;engine=nullptr;
        playing.store(false,std::memory_order_release);
#endif
    }
private:
    bool Fail(){Shutdown();status="UI audio could not start on this device; sounds are unavailable.";return false;}
};
} // namespace KennyAudio
