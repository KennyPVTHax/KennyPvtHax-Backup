// Actual production menu, native controls, original panel statements and fonts.
// The test fixture aborts ResetLogin; no gameplay/SDK replacement is executed.
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
    std::ofstream atlas(".verification/stage5_6-atlas.rgba",std::ios::binary);
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
void IdleUntil(double seconds) {
    for(int i=0;i<1200 && menu.aurora.time<seconds-.004;++i) Frame();
    assert(std::abs(menu.aurora.time-seconds)<.004);
}
int main() {
    InitializeCapture();const auto features=SnapshotFeatures();
    Save("stage5_6-aurora-00");
    IdleUntil(2);Save("stage5_6-aurora-02");
    IdleUntil(3);Save("stage5_6-aurora-03");
    IdleUntil(6);Save("stage5_6-aurora-06");
    IdleUntil(10);Save("stage5_6-aurora-10");Save("stage5_6-idle-stars");
    const auto origin=Origin();const auto layout=KennyMenu::Measure(viewport);
    const ImVec2 center(origin.x+layout.size.x*.5f,origin.y+layout.size.y*.78f);
    const ImVec2 end(origin.x+layout.size.x*.66f,origin.y+layout.size.y*.74f);
    for(int i=0;i<120;++i)Frame(center,true);
    assert(menu.aurora.gesture);Save("stage5_6-center-touch");
    for(int i=1;i<=120;++i) Frame(ImVec2(center.x+(end.x-center.x)*i/120,center.y+(end.y-center.y)*i/120),true);
    Save("stage5_6-dragged-touch");Frame(end,false);Save("stage5_6-release-00");
    for(int i=0;i<120;++i)Frame();Save("stage5_6-release-02");
    for(int i=0;i<480;++i)Frame();Save("stage5_6-release-10");
    menu.appearance.reducedMotion=true;Frame();Save("stage5_6-reduced");menu.appearance.reducedMotion=false;
    assert(features==SnapshotFeatures());

    // Continuous 12-second native interaction, sampled at 12 fps. Physics runs
    // at the native host's 60 Hz input cadence / bounded 120 Hz substeps.
    menu.aurora=KennyAurora::State{};Frame();Save("stage5_6-film-000");
    for(int i=1;i<=720;++i) {
        if(i<=240) Frame();
        else if(i<=360) Frame(center,true);
        else if(i<=480) {const float t=(i-360)/120.0f;Frame(ImVec2(center.x+(end.x-center.x)*t,center.y+(end.y-center.y)*t),true);}
        else Frame();
        if(i%5==0) {
            char name[64];std::snprintf(name,sizeof(name),"stage5_6-film-%03d",i/5);Save(name);
        }
    }
    assert(features==SnapshotFeatures());
    std::puts("PASS actual 1920x872 Player captures: 0/3/6/10 seconds, idle/center/drag/release/reduced, 145 consecutive animation frames, unchanged original feature snapshot.");
    ImGui::DestroyContext();
}
