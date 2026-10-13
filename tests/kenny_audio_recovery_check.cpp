#define KENNY_C3_CAPTURE_NO_MAIN
#include "kenny_c3_capture.cpp"
#include "KennyAndroidAudio.h"
#include <thread>
int main(int argc,char** argv){
    assert(argc==2);using namespace KennyAudioDiagnostics;using namespace KennyCharacters;
    auto registry=std::make_unique<Registry>();registry->Configure(argv[1]);auto bank=std::make_unique<KennyAudio::Bank>();bank->Initialize();KennyAudio::Mixer mixer;mixer.bank=bank.get();KennyAudio::Dispatcher dispatcher;dispatcher.mixer=&mixer;
    KennyAppearance::Preferences p;p.theme=KennyAppearance::Theme::Anime;p.voicePack="user_supplied_events";registry->Prepare(p,&dispatcher);registry->testEvent=VoiceEvent::AimEnabled;
    assert(registry->TestVoice(p,nullptr,1)==Result::EngineUnavailable);
    p.uiSounds=false;assert(registry->TestVoice(p,&dispatcher,2)==Result::SoundDisabled);p.uiSounds=true;
    p.characterVoice=false;assert(registry->TestVoice(p,&dispatcher,3)==Result::VoiceDisabled);p.characterVoice=true;
    p.uiVolume=0;assert(registry->TestVoice(p,&dispatcher,4)==Result::UiVolumeZero);p.uiVolume=35;
    p.characterVolume=0;assert(registry->TestVoice(p,&dispatcher,5)==Result::VoiceVolumeZero);p.characterVolume=70;
    p.theme=KennyAppearance::Theme::Classic;assert(registry->TestVoice(p,&dispatcher,6)==Result::WrongTheme);p.theme=KennyAppearance::Theme::Anime;
    p.characterId="unknown";assert(registry->TestVoice(p,&dispatcher,7)==Result::WrongCharacter);p.characterId="highschool_dxd_rias";
    p.voicePack="uninstalled";assert(registry->TestVoice(p,&dispatcher,8)==Result::WrongPack);p.voicePack="user_supplied_events";
    registry->testEvent=VoiceEvent::BulletDisabled;assert(registry->TestVoice(p,&dispatcher,9)==Result::MissingRecording);registry->testEvent=VoiceEvent::AimEnabled;
    assert(registry->TestVoice(p,&dispatcher,10)==Result::Queued);auto written=mixer.write.load();assert(registry->TestVoice(p,&dispatcher,10.1)==Result::Cooldown&&mixer.write.load()==written);
    std::array<int16_t,4096> pcm{};mixer.Render(pcm.data(),pcm.size());assert(mixer.transport.recordingsStarted==1);bool audiblePcm=false;for(auto value:pcm)audiblePcm|=value!=0;assert(audiblePcm); // actual PCM, not Android speakers
    for(int i=0;i<100;++i)mixer.Render(pcm.data(),pcm.size());
    for(unsigned i=0;i<KennyAudio::QueueSize-1;++i)assert(mixer.Submit(KennyAudio::Event::ButtonPressed,KennyAudio::Profile::Aurora));
    assert(registry->TestVoice(p,&dispatcher,20)==Result::QueueFull);mixer.Render(pcm.data(),pcm.size());
    auto* pack=registry->Pack(registry->characters[0],p.voicePack);assert(pack);pack->events[unsigned(VoiceEvent::AimEnabled)].count=0;pack->decodeFailed[unsigned(VoiceEvent::AimEnabled)]=true;assert(registry->TestVoice(p,&dispatcher,30)==Result::DecodeFailed);pack->events[unsigned(VoiceEvent::AimEnabled)].count=1;
    p.controlVoiceFeedback=false;assert(!Registry::Route(registry.get(),KennyAudio::Event::CheckboxOn,p,31,"Enable aimbot")&&registry->lastResult==Result::ControlDisabled);p.controlVoiceFeedback=true;
    // Callback mailbox is bounded, I/O-free and safe with a producer/consumer.
    Transport transport;std::thread callback([&]{for(int i=0;i<10000;++i)transport.Callback();});callback.join();assert(transport.callbacks==10000&&transport.Drain()==1&&transport.Drain()==0);transport.Callback(7);assert(transport.Drain()==2&&transport.callbackError==7);
    char tmp[]="/tmp/kenny-audio-missing-XXXXXX";const char* empty=mkdtemp(tmp);assert(empty);auto missing=std::make_unique<Registry>();missing->Configure(empty);missing->Prepare(p,&dispatcher);assert(std::strstr(missing->mediaStatus,"missing"));assert(missing->TestVoice(p,&dispatcher,40)==Result::WrongPack);rmdir(empty);
    KennyAudio::AndroidBackend unavailable;assert(!unavailable.Initialize()); // no Android runtime on host; not simulated success
    InitializeC3Capture();auto features=SnapshotFeatures();menu.characters.Configure(argv[1]);menu.appearance.theme=KennyAppearance::Theme::Anime;menu.appearance.voicePack="user_supplied_events";menu.audio=&dispatcher;menu.audioStatus="Portable PCM test sink; Android playback unverified.";Frame();Frame();Primary(4);ResetScroll();Frame();ImGui::SetScrollY(panelWindow,panelWindow->ScrollMax.y);Frame();Frame();
    auto writeBefore=mixer.write.load();Click(NativeCenter("Test Voice"));assert(menu.characters.testResult==Result::Queued&&mixer.write.load()!=writeBefore);assert(features==SnapshotFeatures());
    written=mixer.write.load();Click(NativeCenter("Test Voice"));assert(menu.characters.testResult==Result::Cooldown&&mixer.write.load()==written); // no generic button tone to disguise failure
    menu.audio=nullptr;Frame();Click(NativeCenter("Test Voice"));assert(menu.characters.testResult==Result::EngineUnavailable);
    auto start=KennyDiagnostics::Get().start,count=KennyDiagnostics::Get().count;for(int i=0;i<60;++i)Frame();assert(KennyDiagnostics::Get().start==start&&KennyDiagnostics::Get().count==count);
    Save("audio-recovery-test-unavailable");viewport=ImVec2(640,360);menu.centerRequested=true;Frame();Frame();ImGui::SetScrollY(panelWindow,panelWindow->ScrollMax.y);Frame();Frame();assert(nativeLabels.count("Test Voice"));Click(NativeCenter("Test Voice"));assert(features==SnapshotFeatures());Save("audio-recovery-test-640");menu.audio=nullptr;ImGui::DestroyContext();
    puts("PASS audio recovery: missing media/engine, mute/volumes/theme/character/pack, missing/corrupt event, queue-full and cooldown produce truthful distinct outcomes; direct real PCM test, native Test Voice without feature edits or masking button tones, visible 640 scrolling, no idle logging, callback-safe transport mailbox. Android OpenSL/speakers unverified.");
}
