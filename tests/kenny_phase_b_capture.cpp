// Real application headers/panels/native input; no substitute artwork or SDK.
#define main KennyMenuRegressionMain
#include "kenny_menu_host_check.cpp"
#undef main

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
    std::ofstream atlas(".verification/phase_b-atlas.rgba",std::ios::binary);
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

int main() {
    InitializeCapture();const auto features=SnapshotFeatures();
    char pattern[]="/tmp/kenny-phase-b-capture-XXXXXX";const char* directory=mkdtemp(pattern);assert(directory);
    menu.storage.Configure(directory,menu.appearance);
    const char* names[]={"player","world","aim","bullet","extra","style","settings"};
    const int route[]={0,0,1,2,2,3,4};
    for(int panel=0;panel<7;++panel) {
        if(panel<2)menu.visualTab=panel==1?2:1;
        if(panel==3 || panel==4)menu.miscTab=panel==4?5:4;
        menu.Select(static_cast<KennyMenu::Category>(route[panel]),Settings::Tab);
        ResetScroll();for(int i=0;i<40;++i)Frame();
        menu.aurora=KennyAurora::State{};menu.aurora.time=menu.aurora.particleTime=3;
        Frame();Save((std::string("phase_b-aurora-")+names[panel]).c_str());
        if(panel==5) {
            ImGui::SetScrollY(panelWindow,panelWindow->ScrollMax.y);Frame();Frame();Save("phase_b-aurora-preferences");ResetScroll();
        }
    }
    for(auto theme:{KennyAppearance::Theme::Anime,KennyAppearance::Theme::Classic}) {
        Primary(3);ResetScroll();Click(NativeCenter(KennyAppearance::ThemeName(theme)));
        for(int i=0;i<40;++i)Frame();
        Save((std::string("phase_b-")+(theme==KennyAppearance::Theme::Anime ? "anime-style" : "classic-style")).c_str());
        Primary(0);Secondary(false);ResetScroll();for(int i=0;i<40;++i)Frame();
        Save((std::string("phase_b-")+(theme==KennyAppearance::Theme::Anime ? "anime-player" : "classic-player")).c_str());
    }
    viewport=ImVec2(640,360);menu.centerRequested=true;Frame();Frame();Primary(3);ResetScroll();Save("phase_b-style-640");
    // Labels/card descriptions fit even at the smallest tested landscape size.
    for(const char* label:{"Aurora","Anime","Classic"}) {
        auto c=Native(label);assert(c.max.y-c.min.y>=96 && c.max.x-c.min.x>=ImGui::CalcTextSize(label).x+20);
    }
    assert(features==SnapshotFeatures());
    unlink(menu.storage.path.c_str());rmdir(directory);
    ImGui::DestroyContext();
    std::puts("PASS Phase B actual captures: seven Aurora panels, Aurora preference scroller, Anime missing-artwork/Classic themes and Style cards at 640; original feature snapshot unchanged.");
}
