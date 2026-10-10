// Actual production C3 UI with local CC0 alternative; Rias artwork remains absent.
#define main KennyMenuRegressionMain
#include "kenny_menu_host_check.cpp"
#undef main
#include "KennyLauncher.h"
#include <memory>
void InitializeC3Capture() {
    ImGui::CreateContext();auto& io=ImGui::GetIO();io.IniFilename=nullptr;io.LogFilename=nullptr;
    ImFontConfig cfg;cfg.FontDataOwnedByAtlas=false;
    io.Fonts->AddFontFromMemoryTTF((void*)Custom_data,Custom_size,16,&cfg);
    cfg.MergeMode=true;cfg.PixelSnapH=true;const ImWchar ranges[]={ICON_MIN_FA,ICON_MAX_FA,0};
    io.Fonts->AddFontFromMemoryTTF((void*)fontAwesome,sizeof(fontAwesome),15,&cfg,ranges);
    ImFontConfig menuCfg;menuCfg.FontDataOwnedByAtlas=false;
    KennyMenu::Font=io.Fonts->AddFontFromMemoryTTF((void*)Custom_data,Custom_size,32,&menuCfg);
    ImFontConfig icons=cfg;icons.OversampleH=2;icons.OversampleV=2;
    io.Fonts->AddFontFromMemoryTTF((void*)fontAwesome,sizeof(fontAwesome),30,&icons,ranges);
    unsigned char* pixels;int w,h;io.Fonts->GetTexDataAsRGBA32(&pixels,&w,&h);
    std::ofstream atlas(".verification/c3-atlas.rgba",std::ios::binary);
    atlas.write((char*)&w,4);atlas.write((char*)&h,4);atlas.write((char*)pixels,w*h*4);atlas.close();
    Claude::Apply();ImGui::GetCurrentContext()->TestEngineHookItems=true;
    // Exact representative state recorded in the af8a337 Player capture.
    Cheat::Esp::Line=Cheat::Esp::Skeleton=Cheat::Esp::Health=true;
    Cheat::Esp::Name=Cheat::Esp::Distance=Cheat::Esp::Counter=true;
    Cheat::Esp::Vehicle::Name=Cheat::Esp::Throwable=Cheat::Esp::WeaponName=true;
    Cheat::Aimbot::Enable=false;Cheat::Aimbot::Range=150;Cheat::Aimbot::Smoothing=4;
    Cheat::Aimbot::RecoilSet=1.05f;Cheat::Aimbot::EnableFov=true;Cheat::Aimbot::Radius=300;
    Cheat::Aimbot::ShowFovCircle=true;Cheat::BulletTrack::TrackingAccuracy=3;
    Cheat::Memory::Small=Cheat::Memory::Hit=true;
    Frame();Frame();Frame();menu.aurora=KennyAurora::State{};Frame();
}

int main(){
    InitializeC3Capture();const auto features=SnapshotFeatures();menu.characters.Configure(".");
    const auto settle=[](){for(int i=0;i<40;++i)Frame();};
    assert(menu.characters.count==1&&!menu.characters.characters[0].Installed());
    Primary(3);Click(NativeCenter("Anime"));ResetScroll();settle();Save("c3-anime-style");
    assert(menu.appearance.voicePack=="cici_fyre_mature_female");
    Primary(0);Secondary(false);ResetScroll();settle();Save("c3-anime-player");
    Primary(4);ResetScroll();settle();Save("c3-anime-settings");
    ImGui::SetScrollY(panelWindow,panelWindow->ScrollMax.y);settle();Save("c3-anime-voice");
    auto& character=menu.characters.characters[0];assert(!character.artworkTexture.Valid()&&!character.launcherTexture.Valid()&&character.packCount==1);
    const auto table=panelWindow->GetID("##anime-character");
    auto selector=nativeItems.at(ImHashStr("##voice-pack",0,table));
    Click(NativeSliderPoint(selector,.5f));Frame();Click(NativeCenter("Cici Fyre - English alternative"));Frame();assert(menu.appearance.voicePack=="cici_fyre_mature_female");
    auto bank=std::make_unique<KennyAudio::Bank>();bank->Initialize();KennyAudio::Mixer mixer;mixer.bank=bank.get();KennyAudio::Dispatcher audio;audio.mixer=&mixer;
    menu.audio=&audio;menu.audioStatus="Host PCM test sink; Android playback unverified.";
    Frame();Frame();Click(NativeCenter("Character voice"));Frame();assert(!menu.appearance.characterVoice&&mixer.voiceVolume==0);
    Click(NativeCenter("Character voice"));Frame();assert(menu.appearance.characterVoice);
    auto volume=nativeItems.at(ImHashStr("Voice volume",0,table));auto accepted=audio.accepted;
    Click(NativeSliderPoint(volume,0));Frame();assert(menu.appearance.characterVolume==0&&mixer.voiceVolume==0&&audio.accepted==accepted);
    volume=nativeItems.at(ImHashStr("Voice volume",0,table));Click(NativeSliderPoint(volume,.99f));Frame();assert(menu.appearance.characterVolume==100);
    menu.appearance.characterVolume=70;settle();Save("c3-host-pcm-test-settings");
    ResetScroll();Click(NativeCenter("UI sounds"));Frame();assert(!menu.appearance.uiSounds&&mixer.volume==0);
    Click(NativeCenter("UI sounds"));Frame();assert(menu.appearance.uiSounds);
    std::array<int16_t,4096> buffer{};mixer.Render(buffer.data(),buffer.size());
    menu.audio=nullptr;menu.audioStatus="UI audio unavailable in this host preview.";
    auto drawLauncher=[&](){auto& io=ImGui::GetIO();io.MousePos=ImVec2(-100,-100);io.MouseDown[0]=false;
        ImGui::NewFrame();KennyLauncher::State launcher;KennyLauncher::Draw(launcher,menu.appearance,nullptr,viewport);ImGui::Render();Save("c3-anime-launcher-fallback");};drawLauncher();
    viewport=ImVec2(640,360);menu.centerRequested=true;Frame();Frame();ImGui::SetScrollY(panelWindow,panelWindow->ScrollMax.y);Frame();Frame();
    const auto smallTable=panelWindow->GetID("##anime-character");auto small=nativeItems.at(ImHashStr("##voice-pack",0,smallTable));assert(small.max.y-small.min.y>=36);
    ImGui::SetScrollY(panelWindow,panelWindow->Scroll.y+small.min.y-panelWindow->InnerRect.Min.y-50);Frame();Frame();Save("c3-anime-voice-640");
    viewport=ImVec2(1920,872);menu.centerRequested=true;Frame();Frame();Primary(3);ResetScroll();Click(NativeCenter("Aurora"));Primary(0);Secondary(false);ResetScroll();for(int i=0;i<40;++i)Frame();menu.aurora={};menu.aurora.time=menu.aurora.particleTime=3;Frame();Save("c3-aurora-player");
    Primary(3);ResetScroll();Click(NativeCenter("Classic"));Primary(0);Secondary(false);ResetScroll();for(int i=0;i<40;++i)Frame();Save("c3-classic-player");
    assert(features==SnapshotFeatures());ImGui::DestroyContext();std::puts("PASS C3 actual native pack selector, voice checkbox/volume/global mute, disabled host-backend state, minimum small selector height, safe K/artwork fallback, Aurora/Classic captures and unchanged original feature snapshot. PCM test sink is not Android playback.");
}
