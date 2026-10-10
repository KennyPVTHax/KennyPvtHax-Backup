// Production UI and real native input; missing Rias assets remain missing.
#define main KennyMenuRegressionMain
#include "kenny_menu_host_check.cpp"
#undef main
#include "KennyLauncher.h"
void InitializeCapture() {
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
    std::ofstream atlas(".verification/c2-atlas.rgba",std::ios::binary);
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
    InitializeCapture();const auto features=SnapshotFeatures();menu.characters.Configure(".");
    assert(menu.characters.count==1&&!menu.characters.characters[0].Installed());
    Primary(3);Click(NativeCenter("Anime"));ResetScroll();Frame();Frame();Save("c2-anime-style");
    Primary(0);Secondary(false);ResetScroll();Frame();Save("c2-anime-player");
    Primary(4);ResetScroll();Frame();Save("c2-anime-settings");
    ImGui::SetScrollY(panelWindow,panelWindow->ScrollMax.y);Frame();Frame();Save("c2-anime-voice");
    assert(!menu.characters.characters[0].artworkTexture.Valid()&&!menu.characters.characters[0].launcherTexture.Valid());
    // Native selection remains available even while the media are missing.
    const ImGuiID table=panelWindow->GetID("##anime-character");
    auto selector=nativeItems.at(ImHashStr("##anime-character-id",0,table));
    if(selector.min.y<panelWindow->InnerRect.Min.y){ImGui::SetScrollY(panelWindow,panelWindow->Scroll.y+selector.min.y-panelWindow->InnerRect.Min.y-8);Frame();Frame();selector=nativeItems.at(ImHashStr("##anime-character-id",0,table));}
    Click(NativeSliderPoint(selector,.5f));Frame();Click(NativeCenter("Rias Gremory"));Frame();assert(menu.appearance.characterId=="highschool_dxd_rias");
    // Actual launcher path, same bounded drag/tap geometry. No fake artwork.
    auto drawLauncher=[&](const char* name){auto& io=ImGui::GetIO();io.MousePos=ImVec2(-100,-100);io.MouseDown[0]=false;
        ImGui::NewFrame();KennyLauncher::State launcher;KennyLauncher::Draw(launcher,menu.appearance,nullptr,viewport);ImGui::Render();Save(name);};
    drawLauncher("c2-anime-launcher-fallback");
    viewport=ImVec2(640,360);menu.centerRequested=true;Frame();Frame();ImGui::SetScrollY(panelWindow,panelWindow->ScrollMax.y);Frame();Frame();
    const ImGuiID smallTable=panelWindow->GetID("##anime-character");
    auto smallSelector=nativeItems.at(ImHashStr("##anime-character-id",0,smallTable));
    assert(smallSelector.max.y-smallSelector.min.y>=36);
    ImGui::SetScrollY(panelWindow,panelWindow->Scroll.y+smallSelector.min.y-panelWindow->InnerRect.Min.y-50);Frame();Frame();Save("c2-anime-voice-640");
    viewport=ImVec2(1920,872);menu.centerRequested=true;Frame();Frame();Primary(3);ResetScroll();Click(NativeCenter("Aurora"));Primary(0);Secondary(false);ResetScroll();for(int i=0;i<40;++i)Frame();menu.aurora={};menu.aurora.time=menu.aurora.particleTime=3;Frame();Save("c2-aurora-player");
    Primary(3);ResetScroll();Click(NativeCenter("Classic"));Primary(0);Secondary(false);ResetScroll();for(int i=0;i<40;++i)Frame();Save("c2-classic-player");
    assert(features==SnapshotFeatures());ImGui::DestroyContext();std::puts("PASS C2 actual previews/native missing-asset selection: Anime Player/Style/Settings/voice/launcher/small viewport, Aurora and Classic unchanged, original feature snapshot retained. No Rias art or audio fabricated.");
}
