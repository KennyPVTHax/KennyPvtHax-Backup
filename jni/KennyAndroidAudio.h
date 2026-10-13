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
    unsigned lastError=0;
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
        const SLresult result=(*queue)->Enqueue(queue,block.data(),block.size()*sizeof(int16_t));
        if(result!=SL_RESULT_SUCCESS) {
            self.mixer.transport.Callback(result);
            (*self.play)->SetPlayState(self.play,SL_PLAYSTATE_STOPPED);
            self.playing.store(false,std::memory_order_release);
        }else{self.mixer.transport.buffersSubmitted.fetch_add(1,std::memory_order_relaxed);self.mixer.transport.Callback();}
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
        if(!Check(slCreateEngine(&engineObject,0,nullptr,0,nullptr,nullptr),"OpenSL engine creation failed."))return false;
        if(!Check((*engineObject)->Realize(engineObject,SL_BOOLEAN_FALSE),"OpenSL engine realization failed."))return false;
        if(!Check((*engineObject)->GetInterface(engineObject,SL_IID_ENGINE,&engine),"OpenSL engine interface unavailable."))return false;
        if(!Check((*engine)->CreateOutputMix(engine,&mixObject,0,nullptr,nullptr),"OpenSL output mix creation failed."))return false;
        if(!Check((*mixObject)->Realize(mixObject,SL_BOOLEAN_FALSE),"OpenSL output mix realization failed."))return false;
        SLDataLocator_AndroidSimpleBufferQueue locator={SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE,2};
        SLDataFormat_PCM format={SL_DATAFORMAT_PCM,1,SL_SAMPLINGRATE_48,SL_PCMSAMPLEFORMAT_FIXED_16,
                                SL_PCMSAMPLEFORMAT_FIXED_16,SL_SPEAKER_FRONT_CENTER,SL_BYTEORDER_LITTLEENDIAN};
        SLDataSource source={&locator,&format};
        SLDataLocator_OutputMix output={SL_DATALOCATOR_OUTPUTMIX,mixObject};SLDataSink sink={&output,nullptr};
        const SLInterfaceID ids[]={SL_IID_ANDROIDSIMPLEBUFFERQUEUE};const SLboolean required[]={SL_BOOLEAN_TRUE};
        if(!Check((*engine)->CreateAudioPlayer(engine,&playerObject,&source,&sink,1,ids,required),"OpenSL player creation failed."))return false;
        if(!Check((*playerObject)->Realize(playerObject,SL_BOOLEAN_FALSE),"OpenSL player realization failed."))return false;
        if(!Check((*playerObject)->GetInterface(playerObject,SL_IID_PLAY,&play),"OpenSL play interface unavailable."))return false;
        if(!Check((*playerObject)->GetInterface(playerObject,SL_IID_ANDROIDSIMPLEBUFFERQUEUE,&buffers),"OpenSL buffer queue unavailable."))return false;
        if(!Check((*buffers)->RegisterCallback(buffers,Callback,this),"OpenSL callback registration failed."))return false;
        running.store(true,std::memory_order_release);ready=true;
        dispatcher.mixer=&mixer;status="UI sound profiles are ready.";mixer.transport.native.store(true);
        KennyAudioDiagnostics::Log(KennyAudioDiagnostics::Code::EngineReady,"opensl_ready");
#else
        KennyAudioDiagnostics::Log(KennyAudioDiagnostics::Code::EngineFailed,"android_runtime_unavailable");
#endif
        return ready;
    }
    const char* Status() const{return status;}
    bool Ready() const{return ready;}
    unsigned LastError() const{return lastError;}
    void Pump(const KennyAppearance::Preferences& p) {
        dispatcher.Refresh(p);
#ifdef __ANDROID__
        const unsigned signals=mixer.transport.Drain();
        if(signals&2){unsigned error=mixer.transport.callbackError.exchange(0);KennyAudioDiagnostics::Log(KennyAudioDiagnostics::Code::PlaybackFailed,"callback_enqueue_failed",int(error));Check(error,"OpenSL callback enqueue failed.");return;}
        if(signals&1)KennyAudioDiagnostics::Log(KennyAudioDiagnostics::Code::CallbackObserved,"opensl_consumed_buffer_speakers_unverified");
        // Audio stops its player after a short silent tail. A tap reuses the
        // existing objects/buffers; it never creates/loads a resource.
        if(!ready || playing.load(std::memory_order_acquire) ||
           mixer.read.load(std::memory_order_acquire)==mixer.write.load(std::memory_order_acquire))return;
        if(!Check((*buffers)->Clear(buffers),"OpenSL queue clear failed."))return;idleSamples=0;slot=0;
        mixer.transport.firstCallback.store(false,std::memory_order_release);
        for(auto& block:pcm) {
            mixer.Render(block.data(),block.size());
            if(!Check((*buffers)->Enqueue(buffers,block.data(),block.size()*sizeof(int16_t)),"OpenSL buffer enqueue failed."))return;
            mixer.transport.buffersSubmitted.fetch_add(1,std::memory_order_relaxed);
        }
        playing.store(true,std::memory_order_release);
        if(Check((*play)->SetPlayState(play,SL_PLAYSTATE_PLAYING),"OpenSL play start failed."))KennyAudioDiagnostics::Log(KennyAudioDiagnostics::Code::PlaybackStarted,"opensl_play_requested_speakers_unverified");
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
#ifdef __ANDROID__
    bool Check(SLresult result,const char* reason){if(result==SL_RESULT_SUCCESS)return true;lastError=result;KennyAudioDiagnostics::Log(ready?KennyAudioDiagnostics::Code::PlaybackFailed:KennyAudioDiagnostics::Code::EngineFailed,reason,int(result));Shutdown();status=reason;return false;}
#endif
};
} // namespace KennyAudio
