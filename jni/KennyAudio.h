#pragma once
#include <array>
#include <atomic>
#include <algorithm>
#include <cmath>
#include <cstdint>
#include "KennyThemePreferences.h"

// Shared event vocabulary, including future key integration. No key validation,
// voice recordings, file decoder or voice-pack loader is implemented in C1.
namespace KennyAudio {
enum class Event : unsigned { MenuOpen, MenuClose, CheckboxOn, CheckboxOff, ButtonPressed,
    PrimaryNavigation, SecondaryNavigation, ThemeChanged, KeyFocused, KeyPasted,
    KeySubmitted, KeyAccepted, KeyRejected, Count };
inline constexpr const char* Names[] = {"menu_open","menu_close","checkbox_on","checkbox_off",
    "button_click","primary_navigation","secondary_navigation","theme_changed","key_focused",
    "key_pasted","key_submitted","key_accepted","key_rejected"};
constexpr unsigned EventCount=static_cast<unsigned>(Event::Count);
enum class Profile : unsigned { Aurora, Classic };
constexpr unsigned SampleRate=48000, MaxSamples=9600, VoiceCount=4, QueueSize=32;
struct Clip { std::array<int16_t,MaxSamples> samples{};unsigned length=0; };
struct Bank {
    std::array<std::array<Clip,EventCount>,2> clips{};
    bool initialized=false;
    void Initialize() {
        if(initialized)return;
        constexpr float frequencies[]={390,550,880,620,1040,710,790,660,640,940,720,1080,310};
        for(unsigned profile=0;profile<2;++profile)for(unsigned e=0;e<EventCount;++e) {
            auto& clip=clips[profile][e];
            const bool signature=e==0 || e==1 || e==7;
            const float duration=profile==0 ? (signature?.15f:.065f) : (signature?.075f:.028f);
            clip.length=static_cast<unsigned>(duration*SampleRate);
            const float frequency=frequencies[e]*(profile==0?.63f:1.0f);
            unsigned random=0x713au+e*997+profile*73;double phase=0;
            for(unsigned i=0;i<clip.length;++i) {
                const float t=float(i)/clip.length;
                const float attack=std::min(1.0f,float(i)/(SampleRate*.003f));
                const float envelope=attack*attack*(1-t)*(1-t);
                const float glide=signature ? (e==1 ? -.22f:.24f)*t : 0;
                phase+=6.283185307179586*frequency*(1+glide)/SampleRate;
                random^=random<<13;random^=random>>17;random^=random<<5;
                const float noise=float(random&65535u)/32767.5f-1;
                const float tone=float(std::sin(phase))+.16f*float(std::sin(phase*2));
                const float texture=noise*(profile==0?.018f:.11f)*std::exp(-t*12);
                clip.samples[i]=static_cast<int16_t>(std::clamp((tone*.16f+texture)*envelope,-.25f,.25f)*32767);
            }
        }
        initialized=true;
    }
    const Clip& Get(Profile p,Event e) const {return clips[static_cast<unsigned>(p)][static_cast<unsigned>(e)];}
};
struct Command { Event event=Event::MenuOpen;Profile profile=Profile::Aurora;unsigned epoch=0; };
// One producer (render thread), one consumer (audio callback). The callback
// never allocates, locks, performs I/O or initializes a sound resource.
struct Mixer {
    const Bank* bank=nullptr;
    std::array<Command,QueueSize> queue{};
    std::atomic<unsigned> read{0},write{0},epoch{0},volume{3500};
    struct Voice { const Clip* clip=nullptr;unsigned position=0; };
    std::array<Voice,VoiceCount> voices{};
    float gain=0;
    unsigned consumerEpoch=0;
    void SetVolume(bool enabled,float percent) {
        const unsigned next=enabled && std::isfinite(percent) ? static_cast<unsigned>(std::clamp(percent,0.0f,100.0f)*100) : 0;
        const unsigned old=volume.exchange(next,std::memory_order_relaxed);
        if(old && !next)epoch.fetch_add(1,std::memory_order_release);
    }
    bool Submit(Event event,Profile profile) {
        if(!bank || !bank->initialized || static_cast<unsigned>(event)>=EventCount || static_cast<unsigned>(profile)>1 || !volume.load(std::memory_order_relaxed))return false;
        const unsigned w=write.load(std::memory_order_relaxed),next=(w+1)%QueueSize;
        if(next==read.load(std::memory_order_acquire))return false;
        queue[w]={event,profile,epoch.load(std::memory_order_acquire)};
        write.store(next,std::memory_order_release);return true;
    }
    void Render(int16_t* output,unsigned count) {
        const unsigned currentEpoch=epoch.load(std::memory_order_acquire);
        if(currentEpoch!=consumerEpoch) {for(auto& v:voices)v={};consumerEpoch=currentEpoch;gain=0;}
        unsigned r=read.load(std::memory_order_relaxed);
        const unsigned w=write.load(std::memory_order_acquire);
        for(unsigned n=0;n<QueueSize && r!=w;++n) {
            const auto command=queue[r];r=(r+1)%QueueSize;
            if(command.epoch!=currentEpoch || !volume.load(std::memory_order_relaxed))continue;
            for(auto& voice:voices)if(!voice.clip) {voice={&bank->Get(command.profile,command.event),0};break;}
        }
        read.store(r,std::memory_order_release);
        const float target=volume.load(std::memory_order_relaxed)*.0001f;
        for(unsigned i=0;i<count;++i) {
            gain+=(target-gain)*.004f;float value=0;
            for(auto& v:voices)if(v.clip) {
                value+=v.clip->samples[v.position++]*gain;
                if(v.position>=v.clip->length)v={};
            }
            output[i]=static_cast<int16_t>(std::clamp(value,-32767.0f,32767.0f));
        }
    }
};
struct Dispatcher {
    Mixer* mixer=nullptr;
    std::array<double,EventCount> last{};
    double lastAny=-100;
    unsigned accepted=0,throttled=0;
    Event lastEvent=Event::MenuOpen;
    Dispatcher(){last.fill(-100);}
    Profile Resolve(const KennyAppearance::Preferences& p) const {
        if(p.soundProfile==2)return Profile::Classic;
        if(p.soundProfile==1)return Profile::Aurora;
        return p.theme==KennyAppearance::Theme::Classic ? Profile::Classic : Profile::Aurora;
    }
    void Refresh(const KennyAppearance::Preferences& p) {if(mixer)mixer->SetVolume(p.uiSounds,p.uiVolume);}
    bool Emit(Event e,const KennyAppearance::Preferences& p,double now) {
        Refresh(p);const unsigned i=static_cast<unsigned>(e);
        if(!mixer || !p.uiSounds || p.uiVolume<=0 || i>=EventCount || !std::isfinite(now))return false;
        const bool lifecycle=e==Event::MenuOpen || e==Event::MenuClose;
        if(now<lastAny){last.fill(-100);lastAny=-100;}
        if(now-last[i]<.055 || (!lifecycle && now-lastAny<.022)) {++throttled;return false;}
        if(!mixer->Submit(e,Resolve(p)))return false;
        last[i]=lastAny=now;lastEvent=e;++accepted;return true;
    }
};
struct Context { Dispatcher* dispatcher=nullptr;const KennyAppearance::Preferences* preferences=nullptr;double time=0; };
inline Context current;
struct Scope {
    Context previous;
    Scope(Dispatcher* dispatcher,const KennyAppearance::Preferences& preferences,double time):previous(current) {
        current={dispatcher,&preferences,time};if(dispatcher)dispatcher->Refresh(preferences);
    }
    ~Scope(){current=previous;}
    Scope(const Scope&)=delete;Scope& operator=(const Scope&)=delete;
};
inline void Emit(Event event) {if(current.dispatcher && current.preferences)current.dispatcher->Emit(event,*current.preferences,current.time);}
} // namespace KennyAudio
