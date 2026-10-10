#include "KennyAndroidAudio.h"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <limits>
#include <thread>
#include <memory>
#include <new>
using namespace KennyAudio;
static std::atomic<size_t> allocations{0};
void* operator new(size_t n){allocations.fetch_add(1);if(void* p=std::malloc(n))return p;throw std::bad_alloc();}
void* operator new[](size_t n){return ::operator new(n);}
void operator delete(void* p) noexcept {std::free(p);}
void operator delete[](void* p) noexcept {std::free(p);}
void operator delete(void* p,size_t) noexcept {std::free(p);}
void operator delete[](void* p,size_t) noexcept {std::free(p);}
void WriteWave(const char* path,Profile profile,const Bank& bank) {
    constexpr unsigned frames=SampleRate*3;std::array<int16_t,frames> pcm{};
    Mixer mixer;mixer.bank=&bank;mixer.SetVolume(true,35);
    for(unsigned i=0;i<8;++i){assert(mixer.Submit(static_cast<Event>(i),profile));mixer.Render(pcm.data()+i*SampleRate/3,SampleRate/3);}
    const uint32_t size=frames*2, riff=size+36,fmt=16,rate=SampleRate,bytes=rate*2;
    const uint16_t format=1,channels=1,align=2,bits=16;
    std::ofstream out(path,std::ios::binary);assert(out);
    auto write=[&](const auto& value){out.write(reinterpret_cast<const char*>(&value),sizeof(value));};
    out.write("RIFF",4);write(riff);out.write("WAVEfmt ",8);write(fmt);write(format);write(channels);write(rate);write(bytes);write(align);write(bits);out.write("data",4);write(size);out.write(reinterpret_cast<const char*>(pcm.data()),size);assert(out.good());
}
int main(){
    auto bank=std::make_unique<Bank>();bank->Initialize();auto copy=std::make_unique<Bank>();copy->Initialize();
    assert(bank->clips[0][0].samples==copy->clips[0][0].samples);
    for(unsigned p=0;p<2;++p)for(unsigned e=0;e<EventCount;++e){
        const auto& clip=bank->Get(static_cast<Profile>(p),static_cast<Event>(e));
        assert(clip.length>0 && clip.length<=MaxSamples && clip.samples[0]==0);
        bool nonzero=false;for(unsigned i=0;i<clip.length;++i){assert(std::abs(int(clip.samples[i]))<=8192);nonzero|=clip.samples[i]!=0;}assert(nonzero);
    }
    assert(bank->Get(Profile::Aurora,Event::CheckboxOn).samples!=bank->Get(Profile::Aurora,Event::CheckboxOff).samples);
    assert(bank->Get(Profile::Classic,Event::MenuOpen).length!=bank->Get(Profile::Aurora,Event::MenuOpen).length);
    Mixer mixer;mixer.bank=bank.get();std::array<int16_t,MaxSamples> pcm{};
    assert(!mixer.Submit(Event::Count,Profile::Aurora));assert(!mixer.Submit(Event::MenuOpen,static_cast<Profile>(8)));
    for(unsigned i=0;i<QueueSize-1;++i)assert(mixer.Submit(Event::CheckboxOn,Profile::Aurora));
    assert(!mixer.Submit(Event::MenuOpen,Profile::Aurora));mixer.Render(pcm.data(),1);
    unsigned count=0;for(auto& v:mixer.voices)count+=v.clip!=nullptr;assert(count==VoiceCount);
    mixer.SetVolume(false,100);mixer.Render(pcm.data(),pcm.size());for(auto n:pcm)assert(n==0);
    mixer.SetVolume(true,35);assert(mixer.Submit(Event::MenuOpen,Profile::Aurora));mixer.SetVolume(false,35);mixer.SetVolume(true,35);
    mixer.Render(pcm.data(),pcm.size());for(auto n:pcm)assert(n==0); // old epoch cannot leak on unmute
    mixer.SetVolume(true,std::numeric_limits<float>::quiet_NaN());assert(!mixer.Submit(Event::MenuOpen,Profile::Aurora));
    mixer.SetVolume(true,1000);assert(mixer.volume==10000);
    KennyAppearance::Preferences p;Dispatcher dispatcher;dispatcher.mixer=&mixer;
    assert(dispatcher.Resolve(p)==Profile::Aurora);p.theme=KennyAppearance::Theme::Classic;assert(dispatcher.Resolve(p)==Profile::Classic);
    p.soundProfile=1;assert(dispatcher.Resolve(p)==Profile::Aurora);p.soundProfile=2;assert(dispatcher.Resolve(p)==Profile::Classic);p.soundProfile=0;
    assert(dispatcher.Emit(Event::MenuOpen,p,1));assert(!dispatcher.Emit(Event::MenuOpen,p,1.01));
    assert(!dispatcher.Emit(Event::ButtonPressed,p,1.01));assert(dispatcher.Emit(Event::MenuClose,p,1.01));
    assert(dispatcher.Emit(Event::CheckboxOn,p,1.1));assert(!dispatcher.Emit(Event::CheckboxOn,p,1.12));
    assert(dispatcher.Emit(Event::CheckboxOff,p,1.16));assert(dispatcher.throttled==3);
    p.uiSounds=false;assert(!dispatcher.Emit(Event::CheckboxOn,p,2));p.uiSounds=true;p.uiVolume=0;assert(!dispatcher.Emit(Event::MenuOpen,p,2));p.uiVolume=35;
    assert(!dispatcher.Emit(Event::MenuOpen,p,std::numeric_limits<double>::quiet_NaN()));
    assert(dispatcher.Emit(Event::MenuOpen,p,.1)); // timing reset
    mixer.Render(pcm.data(),pcm.size());
    auto before=dispatcher.accepted;Emit(Event::ButtonPressed);assert(dispatcher.accepted==before);
    {Scope scope(&dispatcher,p,3);Emit(Event::ButtonPressed);}assert(dispatcher.accepted==before+1 && !current.dispatcher);
    mixer.Render(pcm.data(),pcm.size());
    const auto steady=allocations.load();
    for(unsigned i=0;i<20000;++i){dispatcher.Emit(Event::CheckboxOn,p,10+i*.1);mixer.Render(pcm.data(),pcm.size());}
    assert(allocations.load()==steady);
    // Exercise the actual lock-free single-producer/single-consumer protocol.
    std::atomic<bool> done{false};std::thread consumer([&]{std::array<int16_t,256> block{};while(!done || mixer.read!=mixer.write)mixer.Render(block.data(),block.size());});
    for(unsigned i=0;i<50000;++i){mixer.SetVolume(i%13!=0,float(i%101));mixer.Submit(Event::ButtonPressed,Profile::Classic);}done=true;consumer.join();
    AndroidBackend host;assert(!host.Initialize() && !host.Initialize() && !host.Ready());host.Pump(p);assert(!host.dispatcher.mixer);host.Shutdown();
    WriteWave(".verification/c1-aurora.wav",Profile::Aurora,*bank);WriteWave(".verification/c1-classic.wav",Profile::Classic,*bank);
    std::puts("PASS real PCM recipes/mixer: bounded deterministic profiles, distinct toggles, 4 voices/31 commands, mute epochs, finite/clamped volume, missing backend, scoped events, throttling, time reset, 20000 allocation-free dispatch/render iterations, 50000 concurrent SPSC submissions. Generated genuine 48kHz mono PCM demos; Android playback not tested.");
}
