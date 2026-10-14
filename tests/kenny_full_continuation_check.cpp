#include "KennyCharacters.h"
#include "KennyAppearanceStore.h"
#include <cassert>
#include <fstream>
#include <memory>
int main(){
    using namespace KennyAppearance;using namespace KennyCharacters;
    char tmp[]="/tmp/kenny-full-XXXXXX";auto dir=mkdtemp(tmp);assert(dir);
    Preferences p;p.theme=Theme::Anime;p.artworkVisible=false;p.controlVoiceFeedback=false;
    Store store;store.Configure(dir,p);store.Sync(p,true);
    // Configure observes initial values, so explicitly save this first snapshot.
    assert(store.Save(p));Preferences restored;Store restart;restart.Configure(dir,restored);assert(Equal(p,restored));
    for(int version:{3,4}){std::ofstream f(store.path);f<<"KennyPvtHaxAppearance "<<version<<"\n1 88 0 1 40 30 1 1 80 1\n1 66 0\nhighschool_dxd_rias default character.png 1 43 1\n";if(version==4)f<<"bad tail\n";f.close();Preferences old;Store read;read.Configure(dir,old);assert(old.opacity==88&&old.characterVolume==43&&old.artworkVisible&&old.controlVoiceFeedback);}
    unlink(store.path.c_str());rmdir(dir);
    auto registry=std::make_unique<Registry>();registry->Configure(".");auto bank=std::make_unique<KennyAudio::Bank>();bank->Initialize();KennyAudio::Mixer mixer;mixer.bank=bank.get();KennyAudio::Dispatcher audio;audio.mixer=&mixer;
    p=Preferences{};p.theme=Theme::Anime;p.voicePack="cici_fyre_mature_female";registry->Prepare(p,&audio);
    auto* selected=registry->Pack(registry->characters[0],p.voicePack);assert(selected);auto& pack=*selected;
    assert(!pack.events[0].clips[0].samples.empty()&&!pack.events[1].clips[0].samples.empty());
    // Test-only aliases to existing licensed PCM; production recordings/maps unchanged.
    pack.events[unsigned(VoiceEvent::ThemeSwitch)].clips[0]=pack.events[0].clips[0];pack.events[unsigned(VoiceEvent::ThemeSwitch)].count=1;
    pack.events[unsigned(VoiceEvent::SettingsNavigation)].clips[0]=pack.events[1].clips[0];pack.events[unsigned(VoiceEvent::SettingsNavigation)].count=1;
    std::array<int16_t,2048> buffer{};
    assert(audio.Emit(KennyAudio::Event::ThemeChanged,p,1));mixer.Render(buffer.data(),buffer.size());assert(mixer.character==&pack.events[unsigned(VoiceEvent::ThemeSwitch)].clips[0]);
    for(int i=0;i<100;++i)mixer.Render(buffer.data(),buffer.size()); // Advance the PCM clock as well as event time.
    assert(audio.Emit(KennyAudio::Event::PrimaryNavigation,p,5,"Settings"));mixer.Render(buffer.data(),buffer.size());assert(mixer.character==&pack.events[unsigned(VoiceEvent::SettingsNavigation)].clips[0]);
    assert(audio.Emit(KennyAudio::Event::PrimaryNavigation,p,5.1,"Settings"));mixer.Render(buffer.data(),buffer.size());assert(mixer.character==&pack.events[unsigned(VoiceEvent::SettingsNavigation)].clips[0]);
    p.controlVoiceFeedback=false;assert(!Registry::Route(registry.get(),KennyAudio::Event::CheckboxOn,p,10,"ESP line"));assert(!Registry::Route(registry.get(),KennyAudio::Event::ButtonPressed,p,10,nullptr));
    p.uiSounds=false;assert(!Registry::Route(registry.get(),KennyAudio::Event::ThemeChanged,p,11,nullptr));p.uiSounds=true;p.theme=Theme::Classic;assert(!Registry::Route(registry.get(),KennyAudio::Event::ThemeChanged,p,12,nullptr));
    ImGui::CreateContext();auto& io=ImGui::GetIO();io.IniFilename=nullptr;io.DisplaySize=ImVec2(1920,872);unsigned char* pixels;int w,h;io.Fonts->GetTexDataAsRGBA32(&pixels,&w,&h);ImGui::NewFrame();auto* draw=ImGui::GetBackgroundDrawList();
    p.artworkVisible=false;DrawCharacter(draw,{0,0},{1100,700},34,174,{reinterpret_cast<ImTextureID>(3),32,64},p);assert(draw->VtxBuffer.empty());
    p.artworkVisible=true;DrawCharacter(draw,{0,0},{1100,700},34,174,{reinterpret_cast<ImTextureID>(3),32,64},p);assert(draw->VtxBuffer.Size==4);ImGui::EndFrame();ImGui::DestroyContext();
    puts("PASS full continuation: schema4 round-trip/schema3 migration/corrupt-tail retention, visible/hidden draw geometry, optional theme/Settings voice dispatch, cooldown, control feedback opt-out, mute/theme suppression. Test aliases only; no new production dialogue.");
}
