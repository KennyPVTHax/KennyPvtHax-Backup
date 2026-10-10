#include "kenny_host_fixture.h"
#include <cstdint>

static KennyMenu::State menu;
static bool opened = true;
static ImVec2 viewport(1920, 872);
static int callbackCount = 0;
static float frameDelta = 1.0f/60;
static bool menuVisible = true;
static int lastPanel = 0;
static ImGuiWindow* panelWindow = nullptr;
static std::map<ImGuiID,Control> nativeItems;
static std::map<std::string,ImGuiID> nativeLabels;
static float contentSpacing = 0;
static float windowAlpha = 0;

void ImGuiTestEngineHook_ItemAdd(ImGuiContext* ctx, const ImRect& bb, ImGuiID id) {
    auto* window=ctx->CurrentWindow;
    if(!window->ParentWindow || std::string(window->ParentWindow->Name)!="KennyPvtHax")return;
    nativeItems[id]={id,bb.Min,bb.Max};
    panelWindow=window;
    contentSpacing=ImGui::GetStyle().ItemSpacing.y;
    windowAlpha=ImGui::GetStyle().Colors[ImGuiCol_WindowBg].w;
    if(auto* table=ImGui::GetCurrentTable()) {
        const auto& column=table->Columns[table->CurrentColumn];
        if(bb.Max.x>column.WorkMaxX+1) {
            std::fprintf(stderr,"Native item clipped horizontally: id=%u x=%.1f bound=%.1f\n",id,bb.Max.x,column.WorkMaxX);
            std::abort();
        }
    }
}
void ImGuiTestEngineHook_ItemInfo(ImGuiContext*, ImGuiID id, const char* label, ImGuiItemStatusFlags) {
    if(nativeItems.count(id) && *label)nativeLabels[label]=id;
}
void ImGuiTestEngineHook_IdInfo(ImGuiContext*, ImGuiDataType, ImGuiID, const void*) {}
void ImGuiTestEngineHook_IdInfo(ImGuiContext*, ImGuiDataType, ImGuiID, const void*, const void*) {}
void ImGuiTestEngineHook_Log(ImGuiContext*, const char*, ...) {}


void Frame(ImVec2 mouse = ImVec2(-100, -100), bool down = false) {
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = viewport;
    io.DeltaTime = frameDelta;
    io.MousePos = mouse;
    io.MouseDown[0] = down;
    rendered.clear();nativeItems.clear();nativeLabels.clear();
    ImGui::NewFrame();
    if(menuVisible) KennyMenu::Draw(menu, opened, Settings::Tab, viewport, [] {
        ++callbackCount;
        lastPanel = Settings::Tab;
        Panels();
        panelWindow = ImGui::GetCurrentWindow();
    });
    ImGui::Render();
    assert(ImGui::GetCurrentContext()->FontStack.Size == 0);
    assert(ImGui::GetCurrentContext()->ColorStack.Size == 0);
    assert(ImGui::GetCurrentContext()->StyleVarStack.Size == 0);
    const auto l = KennyMenu::Measure(viewport);
    auto* root=ImGui::FindWindowByName("KennyPvtHax");
    const float close=std::max(36.0f,44*l.scale);
    const float left=l.compact?l.padding:l.padding+l.brand;
    const float right=l.compact?l.size.x-l.padding:l.size.x-l.padding-close;
    const float tabWidth=(right-left)/5;
    for(const char* label:{ICON_FA_EYE "  Visual", ICON_FA_CROSSHAIRS "  Aim", ICON_FA_CUBE "  Misc",
                           ICON_FA_PALETTE "  Style", ICON_FA_COG "  Settings"}) {
        const auto text=KennyMenu::Font->CalcTextSizeA(root->CalcFontSize(),FLT_MAX,0,label);
        assert(text.x+8*l.scale<=tabWidth);
    }
}

void Click(ImVec2 p) { Frame(p, false); Frame(p, true); Frame(p, false); }
ImVec2 Origin() { return ImGui::FindWindowByName("KennyPvtHax")->Pos; }
void Primary(int i) {
    const auto l = KennyMenu::Measure(viewport);
    const auto o = Origin();
    const float close = std::max(36.0f, 44.0f * l.scale);
    const float left = l.compact ? l.padding : l.padding + l.brand;
    const float right = l.compact ? l.size.x - l.padding : l.size.x - l.padding - close;
    Click(ImVec2(o.x + left + (i + 0.5f) * (right - left) / 5, o.y + l.navY + l.navHeight * 0.5f));
}
void Secondary(bool right) {
    const auto l = KennyMenu::Measure(viewport); const auto o = Origin();
    Click(ImVec2(o.x + l.size.x * 0.5f + (right ? 55.0f : -55.0f) * l.scale,
                 o.y + l.header + l.secondary * 0.5f));
}

std::vector<double> SnapshotFeatures();
void Save(const char* name) {
    std::ofstream state(std::string(".verification/")+name+".state.json");
    state<<"[";bool first=true;for(double value:SnapshotFeatures()){if(!first)state<<",";state<<value;first=false;}state<<"]";
    std::ofstream details(std::string(".verification/")+name+".presentation.json");
    details<<"{\"time\":"<<menu.effects.time<<",\"opacity\":"<<menu.appearance.opacity<<",\"compact\":"<<menu.appearance.compactRows<<",\"reduced\":"<<menu.appearance.reducedMotion<<",\"aurora_time\":"<<menu.aurora.time<<",\"response\":"<<menu.aurora.response<<",\"gesture\":"<<menu.aurora.gesture<<"}";
    const auto* data = ImGui::GetDrawData();
    std::ofstream out(std::string(".verification/") + name + ".draw", std::ios::binary);
    const int header[] = {static_cast<int>(viewport.x), static_cast<int>(viewport.y), data->CmdListsCount};
    out.write(reinterpret_cast<const char*>(header), sizeof(header));
    for (int i = 0; i < data->CmdListsCount; ++i) {
        const auto* list = data->CmdLists[i];
        const int sizes[] = {list->VtxBuffer.Size, list->IdxBuffer.Size, list->CmdBuffer.Size};
        out.write(reinterpret_cast<const char*>(sizes), sizeof(sizes));
        out.write(reinterpret_cast<const char*>(list->VtxBuffer.Data), sizeof(ImDrawVert) * list->VtxBuffer.Size);
        out.write(reinterpret_cast<const char*>(list->IdxBuffer.Data), sizeof(ImDrawIdx) * list->IdxBuffer.Size);
        for (const auto& cmd : list->CmdBuffer) {
            assert(cmd.UserCallback == nullptr);
            out.write(reinterpret_cast<const char*>(&cmd.ClipRect), sizeof(ImVec4));
            const unsigned values[] = {cmd.ElemCount, cmd.IdxOffset, cmd.VtxOffset};
            out.write(reinterpret_cast<const char*>(values), sizeof(values));
        }
    }
}

Control C(int tab, const char* label) { return controls.at({tab,label}); }
ImVec2 CheckPoint(int tab,const char* label) { auto c=C(tab,label);return ImVec2(c.min.x+18,c.min.y+18); }
ImVec2 SliderPoint(int tab,const char* label,float ratio=.5f) { auto c=C(tab,label);return ImVec2(c.min.x+(c.max.x-c.min.x)*ratio,c.max.y-std::max(36.0f,36*KennyControls::Scale())*.5f); }
void EnsureVisible(int tab,const char* label) {
    auto c=C(tab,label);float delta=0;
    if(c.max.y>panelWindow->InnerRect.Max.y-6)delta=c.max.y-panelWindow->InnerRect.Max.y+6;
    else if(c.min.y<panelWindow->InnerRect.Min.y+6)delta=c.min.y-panelWindow->InnerRect.Min.y-6;
    if(delta!=0){ImGui::SetScrollY(panelWindow,panelWindow->Scroll.y+delta);Frame();Frame();}
}
void ResetScroll() { ImGui::SetScrollY(panelWindow,0);Frame();Frame(); }
Control Native(const char* label) {if(!nativeLabels.count(label)){std::fprintf(stderr,"Missing native label %s viewport %.0f scroll %.1f max %.1f\n",label,viewport.x,panelWindow->Scroll.y,panelWindow->ScrollMax.y);std::abort();} return nativeItems.at(nativeLabels.at(label));}
ImVec2 NativeCenter(const char* label){auto c=Native(label);return ImVec2((c.min.x+c.max.x)*.5f,(c.min.y+c.max.y)*.5f);}
Control Opacity(){auto table=panelWindow->GetID("##appearance");return nativeItems.at(ImHashStr("Menu opacity",0,table));}
ImVec2 NativeSliderPoint(Control c,float ratio){return ImVec2(c.min.x+(c.max.x-c.min.x)*ratio,(c.min.y+c.max.y)*.5f);}
std::vector<double> SnapshotFeatures(){return {static_cast<double>(Cheat::Esp::Line),static_cast<double>(Cheat::Esp::Skeleton),static_cast<double>(Cheat::Esp::Health),static_cast<double>(Cheat::Esp::Box),static_cast<double>(Cheat::Esp::Name),static_cast<double>(Cheat::Esp::Distance),static_cast<double>(Cheat::Esp::Counter),static_cast<double>(Cheat::Esp::Alert),static_cast<double>(Cheat::Esp::LootBox),static_cast<double>(Cheat::Esp::Vehicle::Name),static_cast<double>(Cheat::Esp::Throwable),static_cast<double>(Cheat::Esp::Target),static_cast<double>(Cheat::Esp::WeaponName),static_cast<double>(Cheat::Aimbot::Enable),static_cast<double>(Cheat::Aimbot::Range),static_cast<double>(Cheat::Aimbot::VisCheck),static_cast<double>(Cheat::Aimbot::IgnoreKnock),static_cast<double>(Cheat::Aimbot::IgnoreBot),static_cast<double>(Cheat::Aimbot::Smoothing),static_cast<double>(Cheat::Aimbot::RecoilSet),static_cast<double>(Cheat::Aimbot::EnableFov),static_cast<double>(Cheat::Aimbot::Radius),static_cast<double>(Cheat::Aimbot::ShowFovCircle),static_cast<double>(Cheat::BulletTrack::Enable),static_cast<double>(Cheat::BulletTrack::ForceHeadshotWhenFull),static_cast<double>(Cheat::BulletTrack::TrackingAccuracy),static_cast<double>(Cheat::Memory::Small),static_cast<double>(Cheat::Memory::Hit),static_cast<double>(Cheat::Memory::IPad),static_cast<double>(Cheat::Memory::IslandBp)};}

int main() {
    ImGui::CreateContext(); auto& io=ImGui::GetIO();io.IniFilename=nullptr;io.LogFilename=nullptr;
    io.KeyMap[ImGuiKey_Enter]=13;io.KeyMap[ImGuiKey_Escape]=27;io.KeyMap[ImGuiKey_Backspace]=8;
    ImFontConfig cfg;cfg.FontDataOwnedByAtlas=false;
    io.Fonts->AddFontFromMemoryTTF((void*)Custom_data,Custom_size,16,&cfg);
    cfg.MergeMode=true;cfg.PixelSnapH=true;const ImWchar ranges[]={ICON_MIN_FA,ICON_MAX_FA,0};
    io.Fonts->AddFontFromMemoryTTF((void*)fontAwesome,sizeof(fontAwesome),15,&cfg,ranges);
    ImFontConfig menu_cfg;menu_cfg.FontDataOwnedByAtlas=false;
    KennyMenu::Font=io.Fonts->AddFontFromMemoryTTF((void*)Custom_data,Custom_size,32,&menu_cfg);
    ImFontConfig menu_icons=cfg;menu_icons.OversampleH=2;menu_icons.OversampleV=2;
    io.Fonts->AddFontFromMemoryTTF((void*)fontAwesome,sizeof(fontAwesome),30,&menu_icons,ranges);
    unsigned char* pixels;int w,h;io.Fonts->GetTexDataAsRGBA32(&pixels,&w,&h);
    std::ofstream atlas(".verification/phase_b-regression-atlas.rgba",std::ios::binary);atlas.write((char*)&w,4);atlas.write((char*)&h,4);atlas.write((char*)pixels,w*h*4);atlas.close();
    Claude::Apply();ImGui::GetCurrentContext()->TestEngineHookItems=true;
    Cheat::Esp::Line=Cheat::Esp::Skeleton=Cheat::Esp::Health=Cheat::Esp::Name=Cheat::Esp::Distance=Cheat::Esp::Counter=true;
    Frame();Frame();assert(lastPanel==1);Save("phase_b-regression-player-1920");
    assert(rendered.size()==10);
    Click(CheckPoint(1,"ESP line"));assert(!Cheat::Esp::Line);
    Click(CheckPoint(1,"ESP line"));assert(Cheat::Esp::Line);
    // Native navigation activation is retained under circular artwork.
    ImGui::ActivateItem(C(1,"ESP line").id);Frame();Frame();assert(!Cheat::Esp::Line);
    ImGui::ActivateItem(C(1,"ESP line").id);Frame();Frame();assert(Cheat::Esp::Line);
    Secondary(true);assert(Settings::Tab==2 && lastPanel==2 && rendered.size()==3);
    Cheat::Esp::Throwable=Cheat::Esp::WeaponName=true;Frame();Save("phase_b-regression-world-1920");
    Primary(1);assert(Settings::Tab==3 && lastPanel==3 && rendered.size()==8);
    ResetScroll();
    assert(!Cheat::Aimbot::EnableFov);Click(CheckPoint(3,"Enable FOV"));assert(Cheat::Aimbot::EnableFov);
    Frame();assert(rendered.size()==10 && rendered.count({3,"Aim FOV"}));
    ResetScroll();Save("phase_b-regression-aim-1920");
    float old=Cheat::Aimbot::Range;Click(SliderPoint(3,"Aim range",.85f));assert(Cheat::Aimbot::Range>old && Cheat::Aimbot::Range<=400);
    // Drag endpoints and verify the original limits.
    auto c=C(3,"Aim range");auto start=SliderPoint(3,"Aim range");
    Frame(start);Frame(start,true);Frame(ImVec2(c.max.x,start.y),true);Frame(ImVec2(c.max.x,start.y));assert(Cheat::Aimbot::Range==400);
    Frame(start);Frame(start,true);Frame(ImVec2(c.min.x,start.y),true);Frame(ImVec2(c.min.x,start.y));assert(Cheat::Aimbot::Range==0);
    // Ctrl-click and type a value using native temporary numeric input.
    io.KeyCtrl=true;Click(SliderPoint(3,"Aim range"));io.KeyCtrl=false;Frame();
    assert(ImGui::TempInputIsActive(C(3,"Aim range").id));
    io.AddInputCharactersUTF8("250");Frame();io.KeysDown[13]=true;Frame();io.KeysDown[13]=false;Frame();assert(Cheat::Aimbot::Range==250);
    // Exercise every original float range using the production widgets.
    for (auto test : {std::make_pair("Aim smoothing", &Cheat::Aimbot::Smoothing),
                      std::make_pair("Recoil compensation", &Cheat::Aimbot::RecoilSet),
                      std::make_pair("Aim FOV", &Cheat::Aimbot::Radius)}) {
        const float minimum=std::string(test.first)=="Aim smoothing"?1.0f:0.0f;
        const float maximum=std::string(test.first)=="Aim smoothing"?4.0f:
                            std::string(test.first)=="Aim FOV"?400.0f:2.0f;
        EnsureVisible(3,test.first);auto rect=C(3,test.first);auto point=SliderPoint(3,test.first);
        Frame(point);Frame(point,true);Frame(ImVec2(rect.max.x,point.y),true);Frame(ImVec2(rect.max.x,point.y));
        assert(*test.second==maximum);
        Frame(point);Frame(point,true);Frame(ImVec2(rect.min.x,point.y),true);Frame(ImVec2(rect.min.x,point.y));
        assert(*test.second==minimum);
    }
    Cheat::Aimbot::Smoothing=4;Cheat::Aimbot::RecoilSet=1.05f;Cheat::Aimbot::Radius=300;
    ResetScroll();
    Primary(2);assert(Settings::Tab==4 && lastPanel==4 && rendered.size()==10);
    EnsureVisible(4,"Tracking accuracy");
    Click(SliderPoint(4,"Tracking accuracy",.99f));assert(Cheat::BulletTrack::TrackingAccuracy==3);
    Click(SliderPoint(4,"Tracking accuracy",.01f));assert(Cheat::BulletTrack::TrackingAccuracy==1);
    Secondary(true);assert(Settings::Tab==5 && lastPanel==5 && rendered.size()==4);
    Primary(0);assert(Settings::Tab==2);Secondary(false);assert(Settings::Tab==1);
    Primary(2);assert(Settings::Tab==5);
    Primary(3);assert(menu.category==KennyMenu::Category::Style && rendered.empty());
    int count=callbackCount;Frame();assert(callbackCount==count);
    Primary(4);assert(menu.category==KennyMenu::Category::Settings && rendered.empty());
    count=callbackCount;Frame();assert(callbackCount==count);Primary(0);
    auto original=Origin();auto l=KennyMenu::Measure(viewport);ImVec2 drag(original.x+l.padding+50,original.y+40);
    Frame(drag);Frame(drag,true);Frame(ImVec2(drag.x+60,drag.y+25),true);Frame(ImVec2(drag.x+60,drag.y+25));
    auto moved=Origin();assert(moved.x>original.x+40 && moved.y>original.y+15);Frame();assert(Origin().x==moved.x);
    Click(ImVec2(moved.x+l.size.x-l.padding-22*l.scale,moved.y+l.header*.5f));assert(!opened);opened=true;Frame();
    for(ImVec2 size:{ImVec2(2340,1080),ImVec2(1280,720),ImVec2(960,540),ImVec2(640,360)}) {
        viewport=size;Frame();Frame();l=KennyMenu::Measure(viewport);auto o=Origin();
        assert(o.x>=0 && o.y>=0 && o.x+l.size.x<=size.x+1 && o.y+l.size.y<=size.y+1);
        for(int i=0;i<5;++i){Primary(i);assert((int)menu.category==i);}
        Primary(0);Secondary(false);ResetScroll();
        ImGui::SetWindowPos("KennyPvtHax",ImVec2((size.x-l.size.x)*.5f,(size.y-l.size.y)*.5f));Frame();Frame();
        Save(("phase_b-regression-player-"+std::to_string((int)size.x)).c_str());
        Secondary(true);ResetScroll();Save(("phase_b-regression-world-"+std::to_string((int)size.x)).c_str());
        Primary(1);ResetScroll();Save(("phase_b-regression-aim-"+std::to_string((int)size.x)).c_str());
        if(panelWindow->ScrollMax.y>0){
            float before=panelWindow->Scroll.y;auto origin=Origin();
            ImVec2 point(panelWindow->Pos.x+panelWindow->Size.x-25,panelWindow->Pos.y+80);
            Frame(point);io.MouseWheel=-2;Frame(point);Frame(point);
            assert(panelWindow->Scroll.y>before && Origin().y==origin.y);
            for(int j=0;j<4;++j){io.MouseWheel=-5;Frame(point);Frame(point);}
        }
    }
    // Every original checkbox binding is exercised on the smallest viewport,
    // through its label hit area, after scrolling the real item into view.
    struct BoolCase { int tab;const char* label;bool* value; };
    const BoolCase cases[]={
        {1,"ESP line",&Cheat::Esp::Line},
        {1,"ESP skeleton",&Cheat::Esp::Skeleton},
        {1,"ESP health",&Cheat::Esp::Health},
        {1,"ESP box",&Cheat::Esp::Box},
        {1,"ESP name",&Cheat::Esp::Name},
        {1,"ESP distance",&Cheat::Esp::Distance},
        {1,"Counter",&Cheat::Esp::Counter},
        {1,"Alert",&Cheat::Esp::Alert},
        {1,"Loot box",&Cheat::Esp::LootBox},
        {1,"Vehicle name",&Cheat::Esp::Vehicle::Name},
        {2,"Throwable",&Cheat::Esp::Throwable},
        {2,"Target line",&Cheat::Esp::Target},
        {2,"Enemy weapon",&Cheat::Esp::WeaponName},
        {3,"Enable aimbot",&Cheat::Aimbot::Enable},
        {3,"Visibility check",&Cheat::Aimbot::VisCheck},
        {3,"Ignore knocked",&Cheat::Aimbot::IgnoreKnock},
        {3,"Ignore bot",&Cheat::Aimbot::IgnoreBot},
        {3,"Enable FOV",&Cheat::Aimbot::EnableFov},
        {3,"Show FOV circle",&Cheat::Aimbot::ShowFovCircle},
        {4,"Enable bullet track",&Cheat::BulletTrack::Enable},
        {4,"Enable FOV",&Cheat::Aimbot::EnableFov},
        {4,"Show FOV circle",&Cheat::Aimbot::ShowFovCircle},
        {4,"Force headshot on full",&Cheat::BulletTrack::ForceHeadshotWhenFull},
        {4,"Visibility check",&Cheat::Aimbot::VisCheck},
        {4,"Ignore knocked",&Cheat::Aimbot::IgnoreKnock},
        {4,"Ignore bot",&Cheat::Aimbot::IgnoreBot},
        {5,"Small cross",&Cheat::Memory::Small},
        {5,"X-hit effect",&Cheat::Memory::Hit},
        {5,"iPad view",&Cheat::Memory::IPad},
        {5,"6-hour fixer",&Cheat::Memory::IslandBp}
    };
    for(const auto& item:cases) {
        Primary(item.tab<=2?0:item.tab==3?1:2);
        if(item.tab<=2 || item.tab>=4)Secondary(item.tab==2 || item.tab==5);
        Frame();ResetScroll();EnsureVisible(item.tab,item.label);
        const bool before=*item.value;
        auto rect=C(item.tab,item.label);
        Click(ImVec2(rect.max.x-3,rect.min.y+18));assert(*item.value!=before);
        Frame();EnsureVisible(item.tab,item.label);rect=C(item.tab,item.label);
        Click(ImVec2(rect.max.x-3,rect.min.y+18));assert(*item.value==before);
    }
    // Stage 5-specific behavior checks and preview capture.
    viewport=ImVec2(1920,872);Frame();Frame();
    menu.centerRequested=true;Frame();Frame();
    Primary(2);Secondary(false);ResetScroll();
    assert(rendered.size()==10);
    Click(CheckPoint(4,"Enable FOV"));assert(!Cheat::Aimbot::EnableFov);Frame();assert(rendered.size()==8);
    Click(CheckPoint(4,"Enable FOV"));assert(Cheat::Aimbot::EnableFov);Frame();assert(rendered.size()==10);
    EnsureVisible(4,"Aim range");Click(SliderPoint(4,"Aim range",.75f));float sharedRange=Cheat::Aimbot::Range;
    Primary(1);assert(Cheat::Aimbot::Range==sharedRange && rendered.count({3,"Aim range"}));
    Primary(2);Secondary(true);ResetScroll();
    assert(rendered.size()==4 && nativeLabels.count("Guest Reset"));
    assert(nativeItems.at(nativeLabels.at("Guest Reset")).max.y-nativeItems.at(nativeLabels.at("Guest Reset")).min.y>=36);
    const auto originalFeatures=SnapshotFeatures();
    Primary(3);assert(rendered.empty());ResetScroll();
    auto opacity=Opacity();
    Click(NativeSliderPoint(opacity,.01f));Frame();assert(menu.appearance.opacity==85.0f && std::abs(windowAlpha-.85f)<.001f);
    Click(NativeSliderPoint(Opacity(),.99f));Frame();assert(menu.appearance.opacity==100.0f && std::abs(windowAlpha-1)<.001f);
    auto* root=ImGui::FindWindowByName("KennyPvtHax");
    // Background color is scoped to the menu, not the global overlay palette.
    assert(ImGui::GetStyle().Colors[ImGuiCol_WindowBg].w==Claude::Dark::bg.w);
    Click(NativeCenter("Compact"));Frame();assert(menu.appearance.compactRows);
    assert(std::abs(contentSpacing-6*KennyMenu::Measure(viewport).scale)<.001f);
    Primary(0);Frame();assert(menu.appearance.compactRows && std::abs(contentSpacing-6)<.001f);
    Primary(3);Click(NativeCenter("Standard"));Frame();assert(!menu.appearance.compactRows && std::abs(contentSpacing-10)<.001f);
    // Actual temporary input is bounded for presentation preferences only.
    io.KeyCtrl=true;Click(NativeSliderPoint(Opacity(),.5f));io.KeyCtrl=false;Frame();
    io.AddInputCharactersUTF8("200");Frame();io.KeysDown[13]=true;Frame();io.KeysDown[13]=false;Frame();
    assert(menu.appearance.opacity==100.0f);
    Click(NativeCenter("Compact"));Frame();
    menu.appearance.opacity=89;
    Primary(4);assert(rendered.empty());ResetScroll();
    auto home=Origin();auto layout=KennyMenu::Measure(viewport);ImVec2 handle(home.x+layout.padding+50,home.y+40);
    Frame(handle);Frame(handle,true);Frame(ImVec2(handle.x+70,handle.y+20),true);Frame(ImVec2(handle.x+70,handle.y+20));
    assert(Origin().x>home.x+50);
    Click(NativeCenter("Center window"));Frame();
    assert(std::abs(Origin().x-(viewport.x-layout.size.x)*.5f)<1 && std::abs(Origin().y-(viewport.y-layout.size.y)*.5f)<1);
    assert(menu.appearance.compactRows && menu.appearance.opacity==89);
    Click(NativeCenter("Reset appearance"));Frame();
    assert(menu.appearance.opacity==97 && !menu.appearance.compactRows);
    assert(SnapshotFeatures()==originalFeatures);
    menu.appearance.opacity=91;menu.appearance.compactRows=true;
    auto pos=Origin();Click(ImVec2(pos.x+layout.size.x-layout.padding-22*layout.scale,pos.y+layout.header*.5f));
    assert(!opened);opened=true;Frame();assert(menu.appearance.opacity==91 && menu.appearance.compactRows);
    menu.appearance=KennyAppearance::Preferences{};
    Cheat::Aimbot::Range=150;Cheat::Aimbot::Radius=300;Cheat::BulletTrack::TrackingAccuracy=3;
    Cheat::Memory::Small=true;Cheat::Memory::Hit=true;
    for(ImVec2 size:{ImVec2(1920,872),ImVec2(2340,1080),ImVec2(1280,720),ImVec2(960,540),ImVec2(640,360)}) {
        viewport=size;menu.centerRequested=true;Frame();Frame();layout=KennyMenu::Measure(viewport);
        assert(Origin().x>=0 && Origin().y>=0 && Origin().x+layout.size.x<=viewport.x+1 && Origin().y+layout.size.y<=viewport.y+1);
        for(int primary=0;primary<5;++primary){Primary(primary);assert((int)menu.category==primary);}
        Primary(2);Secondary(false);ResetScroll();assert(rendered.size()==10);
        Save(("phase_b-regression-bullet-"+std::to_string((int)size.x)).c_str());
        Secondary(true);ResetScroll();assert(rendered.size()==4);
        assert(nativeLabels.count("Guest Reset"));Save(("phase_b-regression-extra-"+std::to_string((int)size.x)).c_str());
        Primary(3);ResetScroll();assert(rendered.empty());Save(("phase_b-regression-style-"+std::to_string((int)size.x)).c_str());
        Primary(4);ResetScroll();assert(rendered.empty());Save(("phase_b-regression-settings-"+std::to_string((int)size.x)).c_str());
        if(panelWindow->ScrollMax.y>0){
            float before=panelWindow->Scroll.y;auto fixed=Origin();
            ImVec2 point(panelWindow->Pos.x+panelWindow->Size.x-25,panelWindow->Pos.y+50);
            Frame(point);io.MouseWheel=-2;Frame(point);Frame(point);
            assert(panelWindow->Scroll.y>before && Origin().y==fixed.y);
        }
        // Both spacing presets preserve touch targets and feature accessibility.
        menu.appearance.compactRows=true;Primary(2);Secondary(false);ResetScroll();
        assert(rendered.size()==10);
        menu.appearance.compactRows=false;
    }
    // Stage 5: real menu lifecycle and visual interpolation stay separate
    // from configuration. Ordinary pointer/keyboard tests above remain intact.
    viewport=ImVec2(1920,872);menu.centerRequested=true;Frame();Frame();
    const auto features=SnapshotFeatures();
    for(int i=0;i<180;++i) {
        const int category=(i*3)%5;
        menu.Select(static_cast<KennyMenu::Category>(category),Settings::Tab);
        frameDelta=i%3==0 ? 1.0f/30 : i%3==1 ? 1.0f/60 : 1.0f/120;
        const float previous=menu.indicator;
        Frame();
        assert(menu.indicator>=0 && menu.indicator<=4 && std::isfinite(menu.indicator));
        assert(std::abs(menu.indicator-KennyMotion::Step(previous,category,18,frameDelta))<0.00001f);
        assert(SnapshotFeatures()==features);
    }
    frameDelta=1.0f/60;Primary(1);ResetScroll();Frame();Frame();
    const ImGuiID rangeID=C(3,"Aim range").id;
    Cheat::Aimbot::Range=40;Frame();Frame();
    const float visualBefore=KennyMotion::Sample(rangeID,4,.1f);
    Cheat::Aimbot::Range=360;Frame();
    const float visualAfter=KennyMotion::Sample(rangeID,4,.9f);
    assert(Cheat::Aimbot::Range==360 && visualAfter>visualBefore && visualAfter<.9f);
    Cheat::Aimbot::Range=150;
    const double visibleTime=menu.effects.time;
    const int visibleCallbacks=callbackCount;
    menuVisible=false;
    for(int i=0;i<120;++i) {Frame();assert(ImGui::GetDrawData()->TotalVtxCount==0);}
    assert(menu.effects.time==visibleTime && callbackCount==visibleCallbacks);
    menu.Select(KennyMenu::Category::Settings,Settings::Tab);menuVisible=true;Frame();
    assert(menu.effects.time==visibleTime && menu.effects.reveal<1 && menu.indicator==4);
    // Genuine Full/Reduced preference affects all menu visual motion only.
    viewport=ImVec2(1920,872);Primary(3);ResetScroll();Frame();
    const auto motionFeatures=SnapshotFeatures();
    Click(NativeCenter("Reduced"));Frame();assert(menu.appearance.reducedMotion);
    const double frozen=menu.effects.time;
    for(int frame=0;frame<90;++frame)Frame();
    assert(menu.effects.time==frozen && menu.effects.reveal==1 && !KennyMotion::reduced);
    Primary(0);assert(menu.indicator==0);Secondary(false);
    Primary(2);assert(menu.indicator==2);Secondary(true);
    Primary(3);Click(NativeCenter("Full"));Frame();assert(!menu.appearance.reducedMotion);
    const double resumedTime=menu.effects.time;Frame();assert(menu.effects.time>resumedTime);
    Click(NativeCenter("Reduced"));Frame();Primary(4);
    Click(NativeCenter("Reset appearance"));Frame();
    assert(!menu.appearance.reducedMotion && menu.appearance.opacity==97 && !menu.appearance.compactRows);
    assert(SnapshotFeatures()==motionFeatures);
    viewport=ImVec2(640,360);menu.centerRequested=true;Frame();Frame();Primary(3);ResetScroll();
    const auto appearanceID=panelWindow->GetID("##appearance");
    const auto atmosphereID=ImHashStr("Atmosphere",0,appearanceID);
    auto reducedRect=nativeItems.at(ImHashStr("Reduced",0,atmosphereID));
    ImGui::SetScrollY(panelWindow,panelWindow->Scroll.y+std::max(0.0f,reducedRect.max.y-panelWindow->InnerRect.Max.y+6));
    Frame();Frame();Click(NativeCenter("Reduced"));Frame();assert(menu.appearance.reducedMotion);
    auto smallLayout=KennyMenu::Measure(viewport);auto smallOrigin=Origin();
    Click(ImVec2(smallOrigin.x+smallLayout.size.x-smallLayout.padding-18,smallOrigin.y+18));
    assert(!opened);menuVisible=false;for(int i=0;i<10;++i)Frame();menuVisible=true;opened=true;Frame();
    assert(menu.appearance.reducedMotion && !KennyMotion::reduced);
    Primary(4);ResetScroll();Click(NativeCenter("Reset appearance"));Frame();assert(!menu.appearance.reducedMotion);
    // Return to Full for matched baseline/candidate captures.
    // Capture final steady artwork using the real production draw functions.
    Cheat::Aimbot::EnableFov=true;Cheat::Aimbot::Range=150;Cheat::Aimbot::Radius=300;
    Cheat::Aimbot::Smoothing=4;Cheat::Aimbot::RecoilSet=1.05f;
    menu.appearance=KennyAppearance::Preferences{};
    const char* names[]={"player","world","aim","bullet","extra","style","settings"};
    const int primary[]={0,0,1,2,2,3,4};
    for(ImVec2 size:{ImVec2(1920,872),ImVec2(640,360)}) {
        viewport=size;menu.centerRequested=true;Frame();Frame();
        for(int panel=0;panel<7;++panel) {
            Primary(primary[panel]);
            if(panel<2 || panel==3 || panel==4)Secondary(panel==1 || panel==4);
            ResetScroll();for(int warm=0;warm<30;++warm)Frame();
            menu.effects.time=2-frameDelta;Frame();
            Save((std::string("phase_b-regression-")+names[panel]+"-"+std::to_string((int)size.x)).c_str());
        }
    }
    viewport=ImVec2(1920,872);menu.centerRequested=true;Frame();Frame();
    Primary(0);Secondary(false);ResetScroll();for(int warm=0;warm<30;++warm)Frame();
    const auto timeFeatures=SnapshotFeatures();
    for(int second=2;second<=8;++second) {
        menu.effects.time=second-frameDelta;Frame();
        assert(SnapshotFeatures()==timeFeatures);
        Save((std::string("phase_b-regression-player-t0")+std::to_string(second)+"-1920").c_str());
    }
    menu.effects.time=16-frameDelta;Frame();Save("phase_b-regression-player-t16-1920");
    menu.effects.time=6;menu.appearance.reducedMotion=true;Frame();Save("phase_b-regression-player-reduced-1920");
    menu.appearance.reducedMotion=false;

    // Phase A observes native input only after all real panel widgets finish.
    viewport=ImVec2(1920,872);menu.centerRequested=true;menu.appearance.reducedMotion=false;
    Primary(0);Secondary(false);ResetScroll();menu.aurora=KennyAurora::State{};Frame();Frame();
    const auto phaseFeatures=SnapshotFeatures();const auto phaseOrigin=Origin();
    const auto phaseLayout=KennyMenu::Measure(viewport);
    const ImVec2 touch(phaseOrigin.x+phaseLayout.size.x*.5f,phaseOrigin.y+phaseLayout.size.y*.78f);
    const ImVec2 dragged(phaseOrigin.x+phaseLayout.size.x*.63f,phaseOrigin.y+phaseLayout.size.y*.74f);
    float beforeDistance=0,heldDistance=0;int nearby=0;
    std::array<bool,KennyAurora::StarCount> near{};
    auto metric=[&](ImVec2 a,ImVec2 b){return std::hypot((a.x-b.x)*phaseLayout.size.x/phaseLayout.size.y,a.y-b.y);};
    const ImVec2 target(.5f,.78f);
    for(int i=0;i<KennyAurora::StarCount;++i){near[i]=metric(menu.aurora.stars[i].position,target)<.3f;if(near[i]){beforeDistance+=metric(menu.aurora.stars[i].position,target);++nearby;}}
    // A first press without a prior hover frame must still work in blank content.
    Frame(touch,true);assert(menu.aurora.gesture);
    for(int i=0;i<180;++i)Frame(touch,true);
    assert(menu.aurora.response>.99f && !ImGui::GetCurrentContext()->MovingWindow);
    for(int i=0;i<KennyAurora::StarCount;++i)if(near[i])heldDistance+=metric(menu.aurora.stars[i].position,target);
    assert(nearby>=3 && heldDistance<beforeDistance*.8f);
    assert(Origin().x==phaseOrigin.x && Origin().y==phaseOrigin.y && SnapshotFeatures()==phaseFeatures);
    for(int i=1;i<=90;++i){Frame(ImVec2(touch.x+(dragged.x-touch.x)*i/90,touch.y+(dragged.y-touch.y)*i/90),true);assert(menu.aurora.gesture);}
    Frame(dragged,false);assert(!menu.aurora.gesture && menu.aurora.response>0);
    for(int i=0;i<900;++i)Frame();assert(menu.aurora.response<1e-5f);
    for(int i=0;i<KennyAurora::StarCount;++i)assert(metric(menu.aurora.stars[i].position,KennyAurora::State::Home(i,menu.aurora.time))<.004f);
    assert(SnapshotFeatures()==phaseFeatures);
    // No hover warmup before control press: widgets win on activation frame.
    Frame(CheckPoint(1,"ESP line"),true);assert(!menu.aurora.gesture && menu.aurora.response<1e-5f);
    Frame(CheckPoint(1,"ESP line"));Click(CheckPoint(1,"ESP line"));assert(SnapshotFeatures()==phaseFeatures);
    const ImVec2 header(phaseOrigin.x+30,phaseOrigin.y+40);
    Frame(header,true);Frame(ImVec2(header.x+35,header.y+15),true);assert(!menu.aurora.gesture);
    Frame();assert(Origin().x>phaseOrigin.x+20);menu.centerRequested=true;Frame();Frame();
    // Outside-origin gestures, wheel scrolling, and leaving bounds don't capture.
    Frame(ImVec2(20,20),true);Frame(touch,true);assert(!menu.aurora.gesture);Frame();
    Frame(touch,true);assert(menu.aurora.gesture);Frame(ImVec2(20,20),true);assert(!menu.aurora.gesture);
    Frame(touch,true);assert(!menu.aurora.gesture);Frame();
    Frame();Frame();Secondary(true);const auto paused=menu.aurora.time;
    for(int i=0;i<30;++i)Frame(touch,true);
    assert(menu.aurora.time>paused && menu.aurora.gesture);Frame();Secondary(false);
    menu.appearance.reducedMotion=true;const auto auroraFrozen=menu.aurora.time;
    for(int i=0;i<30;++i)Frame(touch,true);
    assert(menu.aurora.time==auroraFrozen && menu.aurora.response==0 && !menu.aurora.gesture);
    Frame();menu.appearance.reducedMotion=false;Frame();assert(menu.aurora.time>auroraFrozen);
    assert(SnapshotFeatures()==phaseFeatures);
    std::puts("PASS Phase A actual native input: first-press attraction, held/dragged/released inertia and dispersion, no background window move, header drag intact, first-press checkbox ownership, outside-origin/exit cancellation, Aurora across panels and reduced-motion freeze; original features unchanged.");

    // Phase B: native theme cards switch the actual renderer immediately.
    using Theme=KennyAppearance::Theme;
    const auto themeFeatures=SnapshotFeatures();
    viewport=ImVec2(1920,872);menu.centerRequested=true;Frame();Primary(3);ResetScroll();
    for(int cycle=0;cycle<30;++cycle)for(Theme theme:{Theme::Classic,Theme::Anime,Theme::Aurora}) {
        Click(NativeCenter(KennyAppearance::ThemeName(theme)));
        assert(menu.appearance.theme==theme && SnapshotFeatures()==themeFeatures);
        const int frame=ImGui::GetFrameCount();
        if(theme!=Theme::Aurora) assert(menu.aurora.frame!=frame && !menu.aurora.gesture);
        else assert(menu.aurora.frame==frame);
    }
    // Aurora controls affect real geometry/physics, without changing features.
    auto prefSlider=[&](const char* label) {
        const auto id=ImHashStr(label,0,panelWindow->GetID("##aurora-settings"));
        return nativeItems.at(id);
    };
    auto intoView=[&](Control c) {
        float delta=0;
        if(c.max.y>panelWindow->InnerRect.Max.y-6)delta=c.max.y-panelWindow->InnerRect.Max.y+6;
        else if(c.min.y<panelWindow->InnerRect.Min.y+6)delta=c.min.y-panelWindow->InnerRect.Min.y-6;
        ImGui::SetScrollY(panelWindow,panelWindow->Scroll.y+delta);Frame();Frame();
    };
    intoView(prefSlider("Aurora intensity"));
    Click(NativeSliderPoint(prefSlider("Aurora intensity"),0));Frame();assert(menu.appearance.auroraIntensity==0);
    const int dimVertices=ImGui::GetDrawData()->TotalVtxCount;
    Click(NativeSliderPoint(prefSlider("Aurora intensity"),.99f));Frame();assert(menu.appearance.auroraIntensity==100);
    assert(ImGui::GetDrawData()->TotalVtxCount>dimVertices+5000);
    intoView(prefSlider("Particle activity"));
    Click(NativeSliderPoint(prefSlider("Particle activity"),0));Frame();assert(menu.appearance.particleActivity==0);
    auto stars=menu.aurora.stars;const auto particleTime=menu.aurora.particleTime, lightTime=menu.aurora.time;
    for(int i=0;i<60;++i)Frame();assert(menu.aurora.particleTime==particleTime && menu.aurora.time>lightTime);
    for(int i=0;i<KennyAurora::StarCount;++i)assert(stars[i].position.x==menu.aurora.stars[i].position.x && stars[i].position.y==menu.aurora.stars[i].position.y);
    Click(NativeSliderPoint(prefSlider("Particle activity"),.99f));Frame();assert(menu.appearance.particleActivity==100);
    intoView(Native("Show stars"));Click(NativeCenter("Show stars"));Frame();assert(!menu.appearance.starsVisible);
    stars=menu.aurora.stars;for(int i=0;i<60;++i)Frame();
    for(int i=0;i<KennyAurora::StarCount;++i)assert(stars[i].position.x==menu.aurora.stars[i].position.x && stars[i].position.y==menu.aurora.stars[i].position.y);
    Click(NativeCenter("Show stars"));Frame();assert(menu.appearance.starsVisible);
    intoView(Native("Touch attraction"));Click(NativeCenter("Touch attraction"));Frame();assert(!menu.appearance.touchAttraction);
    Primary(0);Secondary(false);ResetScroll();const auto loc=Origin();const auto measure=KennyMenu::Measure(viewport);
    const ImVec2 empty(loc.x+measure.size.x*.5f,loc.y+measure.size.y*.78f);
    Frame(empty,true);Frame(empty,true);assert(!menu.aurora.gesture);Frame();
    menu.appearance.touchAttraction=true;
    // All seven routes flow in Aurora. Inactive themes pause the entire state.
    for(Theme theme:{Theme::Aurora,Theme::Anime,Theme::Classic}) {
        menu.appearance.theme=theme;Frame();
        for(int panel=0;panel<7;++panel) {
            if(panel<2)menu.visualTab=panel==1?2:1;
            if(panel==3 || panel==4)menu.miscTab=panel==4?5:4;
            menu.Select(static_cast<KennyMenu::Category>(primary[panel]),Settings::Tab);
            Frame();const auto prior=menu.aurora.time;Frame();
            assert(theme==Theme::Aurora ? menu.aurora.time>prior : menu.aurora.time==prior);
            if(panel<5)assert(callbackCount>0 && !rendered.empty());else assert(rendered.empty());
        }
        Primary(0);Secondary(false);ResetScroll();bool line=Cheat::Esp::Line;
        Click(CheckPoint(1,"ESP line"));assert(Cheat::Esp::Line!=line);Click(CheckPoint(1,"ESP line"));assert(Cheat::Esp::Line==line);
        Primary(1);ResetScroll();float range=Cheat::Aimbot::Range;
        Click(SliderPoint(3,"Aim range",.55f));assert(Cheat::Aimbot::Range!=range);Cheat::Aimbot::Range=range;
    }
    // Every original checkbox remains touch-accessible under every theme,
    // including the smallest viewport and native scroll ownership.
    for(Theme theme:{Theme::Aurora,Theme::Anime,Theme::Classic}) {
        menu.appearance.theme=theme;viewport=ImVec2(640,360);menu.centerRequested=true;Frame();Frame();
        for(const auto& item:cases) {
            Primary(item.tab<=2?0:item.tab==3?1:2);
            if(item.tab<=2 || item.tab>=4)Secondary(item.tab==2 || item.tab==5);
            Frame();ResetScroll();EnsureVisible(item.tab,item.label);
            const bool before=*item.value;auto rect=C(item.tab,item.label);
            Click(ImVec2(rect.max.x-3,rect.min.y+18));assert(*item.value!=before);
            Frame();EnsureVisible(item.tab,item.label);rect=C(item.tab,item.label);
            Click(ImVec2(rect.max.x-3,rect.min.y+18));assert(*item.value==before);
        }
    }
    viewport=ImVec2(1920,872);menu.centerRequested=true;Frame();Frame();
    static int providerCalls=0;
    menu.artwork.SetProvider([](void*,double,bool,KennyThemeBackground::ArtworkFrame& frame) {
        ++providerCalls;frame={reinterpret_cast<ImTextureID>(1),1920,1080};return true;
    },nullptr);
    menu.appearance.theme=Theme::Anime;Frame();assert(providerCalls==1);
    menu.appearance.reducedMotion=true;for(int i=0;i<60;++i)Frame();assert(providerCalls==1);
    menu.appearance.theme=Theme::Classic;const auto artworkTime=menu.artwork.time;
    for(int i=0;i<60;++i)Frame();assert(providerCalls==1 && menu.artwork.time==artworkTime);
    menu.appearance.theme=Theme::Aurora;for(int i=0;i<60;++i)Frame();assert(providerCalls==1);
    menu.artwork.Clear();menu.appearance=KennyAppearance::Preferences{};
    assert(SnapshotFeatures()==themeFeatures);
    std::puts("PASS Phase B: 90 native card switches, immediate routing, Aurora on all seven panels, functional intensity/activity/star/touch controls, all 30 original checkbox sites under all three themes at 640, all theme routes/control access, inactive physics/provider pause, Reduced artwork frame hold, unchanged feature snapshots.");

    // Warm every actual route before observing ImGui allocations/capacities.
    auto cycle=[&](int i) {
        const int panel=i%7;
        menu.appearance.theme=static_cast<Theme>((i/7)%3);
        if(panel<2)menu.visualTab=panel==1?2:1;
        if(panel==3 || panel==4)menu.miscTab=panel==4?5:4;
        menu.Select(static_cast<KennyMenu::Category>(primary[panel]),Settings::Tab);
        Frame();
    };
    for(int i=0;i<140;++i)cycle(i);
    std::map<ImDrawList*,std::pair<int,int>> capacity;
    const int warmedAllocations=io.MetricsActiveAllocations;
    for(int i=0;i<42;++i){cycle(i);const auto* data=ImGui::GetDrawData();for(int l=0;l<data->CmdListsCount;++l){auto* d=data->CmdLists[l];capacity[d]={d->VtxBuffer.Capacity,d->IdxBuffer.Capacity};}}
    for(int i=0;i<1000;++i) {
        cycle(i);assert(io.MetricsActiveAllocations==warmedAllocations);
        const auto* data=ImGui::GetDrawData();
        for(int l=0;l<data->CmdListsCount;++l){auto* d=data->CmdLists[l];assert(capacity.at(d)==std::make_pair(d->VtxBuffer.Capacity,d->IdxBuffer.Capacity));}
    }
    std::puts("PASS actual seven-panel menu: stable warmed ImGui active allocations and draw buffer capacities across 1000 route-switching frames.");
    std::puts("PASS Stage 5.5: Full/Reduced native choice at 1920/640, scoped transitions, clock freeze/resume, immediate indicators, reset/close/reopen and unchanged original feature snapshots.");
    std::puts("PASS Stage 5: rapid category targets at 30/60/120 Hz, inactive slider artwork with immediate real values, hidden menu submits no geometry/callbacks or clock updates, resume indicator snap, and real seven-panel/time-sample captures.");
    std::puts("PASS Stage 5: original panel counts/bindings, native checkbox navigation, float drag limits, Ctrl-click numeric entry, integer slider limits, category/subtab memory, reserved isolation, drag/close/reopen, viewport fit, no horizontal control clipping, scrolling, and balanced stacks.");
    ImGui::DestroyContext();
    return 0;
}
