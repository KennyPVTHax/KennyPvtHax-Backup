#define KENNY_C3_CAPTURE_NO_MAIN
#include "kenny_c3_capture.cpp"

int main(){
    InitializeC3Capture();const auto initial=SnapshotFeatures();
    menu.appearance.theme=KennyAppearance::Theme::Classic;Frame();Frame();ResetScroll();
    menu.electric.time=0;Frame();Save("electric-before");
    menu.appearance.electricStarfield=false;Frame();Save("electric-disabled");menu.appearance.electricStarfield=true;
    menu.electric.time=0;Frame();Save("electric-classic-00");
    for(int i=0;i<180;++i)Frame();Save("electric-classic-03");
    for(int i=0;i<180;++i)Frame();Save("electric-classic-06");
    for(int i=0;i<240;++i)Frame();Save("electric-classic-10");
    menu.electric.time=1.9;Frame();Save("electric-pulse");
    Primary(4);ResetScroll();for(int i=0;i<5;++i)Frame();
    auto makeVisible=[](const char* name){const auto rect=Native(name);ImGui::SetScrollY(panelWindow,panelWindow->Scroll.y+rect.min.y-panelWindow->InnerRect.Min.y-30);Frame();Frame();};
    makeVisible("Enable Electric Starfield");Save("electric-settings");
    Click(NativeCenter("Enable Electric Starfield"));assert(!menu.appearance.electricStarfield);
    Click(NativeCenter("Enable Electric Starfield"));assert(menu.appearance.electricStarfield);
    makeVisible("Energy Pulses");
    for(const char* choice:{"High","Low","Medium"}){
        auto density=nativeItems.at(ImHashStr("##electric-density",0,panelWindow->GetID("##classic-effects")));
        Click(NativeSliderPoint(density,.5f));Frame();Click(NativeCenter(choice));Frame();
        assert(menu.appearance.electricDensity==(std::string(choice)=="High"?2:std::string(choice)=="Low"?0:1));
    }
    makeVisible("Energy Pulses");Click(NativeCenter("Energy Pulses"));assert(!menu.appearance.electricPulses);Click(NativeCenter("Energy Pulses"));assert(menu.appearance.electricPulses);
    makeVisible("Reduced Motion");Click(NativeCenter("Reduced Motion"));assert(menu.appearance.electricReducedMotion);
    const double frozen=menu.electric.time;Frame();Frame();assert(menu.electric.time==frozen);Click(NativeCenter("Reduced Motion"));assert(!menu.appearance.electricReducedMotion);
    for(const char* label:{"Lightning intensity","Sparkle intensity","Animation speed"}){const auto id=ImHashStr(label,0,panelWindow->GetID("##classic-effects"));auto rect=nativeItems.at(id);ImGui::SetScrollY(panelWindow,panelWindow->Scroll.y+rect.min.y-panelWindow->InnerRect.Min.y-30);Frame();Frame();rect=nativeItems.at(id);Click(NativeSliderPoint(rect,0));}
    assert(menu.appearance.electricLightning==0&&menu.appearance.electricSparkle==0&&menu.appearance.electricSpeed==0);
    menu.appearance=KennyAppearance::Preferences{};menu.appearance.theme=KennyAppearance::Theme::Classic;
    Primary(0);ResetScroll();menu.appearance.electricReducedMotion=true;Frame();Save("electric-reduced");menu.appearance.electricReducedMotion=false;
    // Closed/inactive theme frames must not update Classic's clock.
    const double classic=menu.electric.time;menu.appearance.theme=KennyAppearance::Theme::Aurora;for(int i=0;i<30;++i)Frame();assert(menu.electric.time==classic);menu.aurora={};menu.aurora.time=3;menu.indicator=0;Frame();Save("electric-aurora");
    menu.appearance.theme=KennyAppearance::Theme::Anime;for(int i=0;i<30;++i)Frame();assert(menu.electric.time==classic);Save("electric-anime");
    menuVisible=false;for(int i=0;i<12;++i)Frame();assert(menu.electric.time==classic);menuVisible=true;
    menu.appearance.theme=KennyAppearance::Theme::Classic;Frame();assert(menu.electric.time==classic);
    for(int panel=1;panel<=5;++panel){menu.Select(panel==1||panel==2?KennyMenu::Category::Visual:panel==3?KennyMenu::Category::Aim:KennyMenu::Category::Misc,Settings::Tab);Settings::Tab=panel;Frame();ResetScroll();Frame();Save(("electric-panel-"+std::to_string(panel)).c_str());}
    viewport=ImVec2(640,360);menu.centerRequested=true;menu.Select(KennyMenu::Category::Visual,Settings::Tab);Settings::Tab=1;Frame();Frame();Save("electric-small");
    viewport=ImVec2(2560,1440);menu.centerRequested=true;Frame();Frame();Save("electric-large");
    viewport=ImVec2(1280,720);menu.centerRequested=true;Settings::Tab=1;Frame();Frame();menu.electric={};
    for(int i=0;i<=144;++i){Frame();{char label[64];std::snprintf(label,sizeof(label),"electric-motion-%03d",i);Save(label);}
        for(int j=0;j<4;++j)Frame();}
    assert(initial==SnapshotFeatures());ImGui::DestroyContext();
    std::puts("PASS actual electric settings input, hidden/theme clock pause/resume, seven routes, real snapshots, small/large viewport, unchanged 37 feature snapshot; consecutive renderer motion frames captured.");
}
