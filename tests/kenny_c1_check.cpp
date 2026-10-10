// Actual production launcher/menu/input, with the real portable PCM dispatcher.
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

#include "KennyLauncher.h"
#include "KennyAndroidAudio.h"
#include <memory>
static KennyLauncher::State launcher;
static std::unique_ptr<KennyAudio::Bank> bank;
static KennyAudio::Mixer mixer;
static KennyAudio::Dispatcher audio;
static std::array<int16_t,9600> block{};
void CFrame(ImVec2 mouse=ImVec2(-100,-100),bool down=false){
    auto& io=ImGui::GetIO();io.DisplaySize=viewport;io.DeltaTime=frameDelta;io.MousePos=mouse;io.MouseDown[0]=down;
    rendered.clear();nativeItems.clear();nativeLabels.clear();ImGui::NewFrame();
    KennyLauncher::Draw(launcher,menu.appearance,menu.audio,viewport);
    launcher.Advance(io.DeltaTime,menu.appearance.reducedMotion);
    if(launcher.DrawMenu()){
        bool visible=true;
        KennyMenu::Draw(menu,visible,Settings::Tab,viewport,[]{lastPanel=Settings::Tab;Panels();panelWindow=ImGui::GetCurrentWindow();},launcher.alpha,launcher.target);
        if(!visible)launcher.Request(false,menu.appearance,menu.audio,ImGui::GetTime());
    }
    ImGui::Render();mixer.Render(block.data(),block.size());
    auto* ctx=ImGui::GetCurrentContext();assert(ctx->FontStack.Size==0 && ctx->ColorStack.Size==0 && ctx->StyleVarStack.Size==0);
}
void CClick(ImVec2 point){CFrame(point);CFrame(point,true);CFrame(point);}
void Settle(){for(int i=0;i<16;++i)CFrame();}
ImVec2 LCenter(){const float side=KennyLauncher::Side(viewport);return ImVec2(launcher.position.x+side*.5f,launcher.position.y+side*.5f);}
void CPrimary(int i){const auto l=KennyMenu::Measure(viewport);auto o=Origin();const float close=std::max(36.0f,44*l.scale);float left=l.compact?l.padding:l.padding+l.brand,right=l.compact?l.size.x-l.padding:l.size.x-l.padding-close;CClick(ImVec2(o.x+left+(i+.5f)*(right-left)/5,o.y+l.navY+l.navHeight*.5f));}
void CSecondary(bool right){auto l=KennyMenu::Measure(viewport);auto o=Origin();CClick(ImVec2(o.x+l.size.x*.5f+(right?55:-55)*l.scale,o.y+l.header+l.secondary*.5f));}
void Close(){auto l=KennyMenu::Measure(viewport);auto o=Origin();CClick(ImVec2(o.x+l.size.x-l.padding-std::max(36.0f,44*l.scale)*.5f,o.y+(l.compact?l.navY:l.header)*.5f));}
int main(){
    InitializeCapture();bank=std::make_unique<KennyAudio::Bank>();bank->Initialize();mixer.bank=bank.get();audio.mixer=&mixer;menu.audio=&audio;menu.audioStatus="Host: actual PCM mixer test, not Android playback.";
    const auto features=SnapshotFeatures();CFrame();CFrame();
    auto p=LCenter();const unsigned baseline=audio.accepted;
    CClick(ImVec2(1800,800));assert(!launcher.target && audio.accepted==baseline);
    CFrame(p,true);CFrame(ImVec2(p.x+90,p.y+60),true);CFrame(ImVec2(p.x+90,p.y+60));
    assert(!launcher.target && launcher.dragged && audio.accepted==baseline && launcher.position.x>70);
    CClick(LCenter());assert(launcher.target && audio.accepted==baseline+1 && audio.lastEvent==KennyAudio::Event::MenuOpen);
    assert(launcher.alpha>0 && launcher.alpha<1);Save("c1-opening");Settle();assert(launcher.alpha==1);Save("c1-player");
    unsigned count=audio.accepted;for(int i=0;i<10;++i)CFrame();assert(audio.accepted==count);
    CClick(CheckPoint(1,"ESP line"));assert(!Cheat::Esp::Line && audio.accepted==count+1 && audio.lastEvent==KennyAudio::Event::CheckboxOff);
    Settle();CClick(CheckPoint(1,"ESP line"));assert(Cheat::Esp::Line && audio.lastEvent==KennyAudio::Event::CheckboxOn);
    Settle();count=audio.accepted;CPrimary(0);assert(audio.accepted==count);CPrimary(1);assert(audio.accepted==count+1 && lastPanel==3);
    Settle();count=audio.accepted;auto slider=SliderPoint(3,"Aim range");const float old=Cheat::Aimbot::Range;
    CFrame(slider);CFrame(slider,true);CFrame(ImVec2(slider.x+40,slider.y),true);CFrame(ImVec2(slider.x+40,slider.y));
    assert(Cheat::Aimbot::Range!=old && audio.accepted==count);Cheat::Aimbot::Range=old;
    CPrimary(0);Settle();count=audio.accepted;CSecondary(true);assert(lastPanel==2 && audio.accepted==count+1 && audio.lastEvent==KennyAudio::Event::SecondaryNavigation);
    Settle();count=audio.accepted;ImVec2 empty(panelWindow->InnerRect.Min.x+100,panelWindow->InnerRect.Max.y-30);
    CFrame(empty);for(int i=0;i<20;++i)CFrame(empty,true);CFrame(empty);assert(audio.accepted==count);
    CPrimary(3);Settle();CClick(NativeCenter("Classic"));assert(menu.appearance.theme==KennyAppearance::Theme::Classic && audio.lastEvent==KennyAudio::Event::ThemeChanged && audio.Resolve(menu.appearance)==KennyAudio::Profile::Classic);
    Settle();count=audio.accepted;CClick(NativeCenter("Classic"));assert(audio.accepted==count);
    CPrimary(4);Settle();Save("c1-audio-test-settings");
    count=audio.accepted;CClick(NativeCenter("Center window"));assert(audio.accepted==count+1 && audio.lastEvent==KennyAudio::Event::ButtonPressed);
    Settle();auto audioTable=panelWindow->GetID("##ui-audio");
    auto volume=nativeItems.at(ImHashStr("UI sound volume",0,audioTable));
    CClick(NativeSliderPoint(volume,.65f));assert(menu.appearance.uiVolume>55 && menu.appearance.uiVolume<75);
    Settle();auto profile=nativeItems.at(ImHashStr("##sound-profile",0,audioTable));
    CClick(NativeSliderPoint(profile,.5f));
    CFrame();CClick(NativeCenter("Aurora / soft"));
    assert(menu.appearance.soundProfile==1);
    Settle();CClick(NativeCenter("UI sounds"));assert(!menu.appearance.uiSounds);Settle();count=audio.accepted;CPrimary(2);assert(audio.accepted==count);
    menu.appearance.uiSounds=true;menu.appearance.uiVolume=35;CPrimary(1);Settle();const auto route=menu.category;const auto tab=Settings::Tab;
    auto o=Origin();count=audio.accepted;Close();assert(!launcher.target && audio.accepted==count+1 && audio.lastEvent==KennyAudio::Event::MenuClose);
    assert(launcher.alpha>0);Save("c1-closing");
    const bool aimEnable=Cheat::Aimbot::Enable;count=audio.accepted;
    CClick(CheckPoint(3,"Enable aimbot"));assert(Cheat::Aimbot::Enable==aimEnable && audio.accepted==count);
    Settle();assert(launcher.alpha==0);Save("c1-launcher-classic");
    CClick(LCenter());Settle();assert(menu.category==route && Settings::Tab==tab && Origin().x==o.x && Origin().y==o.y);
    // Reduced motion is immediate; outside and drag never masquerade as taps.
    menu.appearance.reducedMotion=true;Close();assert(!launcher.DrawMenu());CClick(LCenter());assert(launcher.alpha==1);
    for(auto theme:{KennyAppearance::Theme::Aurora,KennyAppearance::Theme::Anime,KennyAppearance::Theme::Classic}){
        menu.appearance.theme=theme;Close();Settle();Save(theme==KennyAppearance::Theme::Aurora?"c1-launcher-aurora":theme==KennyAppearance::Theme::Anime?"c1-launcher-anime":"c1-launcher-classic");CClick(LCenter());Settle();
    }
    for(ImVec2 size:{ImVec2(2340,1080),ImVec2(1920,872),ImVec2(1280,720),ImVec2(960,540),ImVec2(640,360)}){
        viewport=size;CFrame();CFrame();Close();launcher.position=ImVec2(10000,10000);CFrame();const float side=KennyLauncher::Side(viewport);
        if(launcher.target || launcher.position.x+side>size.x+1 || launcher.position.y+side>size.y+1)
            std::fprintf(stderr,"launcher fit viewport %.0fx%.0f target %d alpha %.2f pos %.0f,%.0f side %.0f\n",size.x,size.y,launcher.target,launcher.alpha,launcher.position.x,launcher.position.y,side);
        assert(launcher.position.x>=0 && launcher.position.y>=0 && launcher.position.x+side<=size.x+1 && launcher.position.y+side<=size.y+1);
        CClick(LCenter());assert(launcher.target);Settle();
    }
    // The real texture reference rejects invalid geometry; Clear relinquishes
    // the reference before the external owner deletes its texture.
    launcher.logo.Set({nullptr,100,100});assert(!launcher.logo.image.Valid());
    launcher.logo.Set({reinterpret_cast<ImTextureID>(1),512,256});assert(launcher.logo.image.Valid());launcher.logo.Clear();assert(!launcher.logo.image.Valid());
    viewport=ImVec2(1920,872);menu.centerRequested=true;menu.appearance=KennyAppearance::Preferences{};Settle();
    // Genuine host backend unavailable: expose honest disabled controls.
    menu.audio=nullptr;menu.audioStatus="UI audio unavailable in this host preview.";CPrimary(4);Settle();Save("c1-settings");
    viewport=ImVec2(640,360);menu.centerRequested=true;Settle();ImGui::SetScrollY(panelWindow,panelWindow->ScrollMax.y);CFrame();CFrame();Save("c1-settings-640");
    // Warm launcher and fade paths before checking native active allocations.
    viewport=ImVec2(1920,872);menu.centerRequested=true;menu.appearance.reducedMotion=false;
    for(int i=0;i<10;++i){launcher.Request(false,menu.appearance,nullptr,ImGui::GetTime());Settle();CClick(LCenter());Settle();}
    const int allocations=ImGui::GetIO().MetricsActiveAllocations;
    for(int i=0;i<100;++i){launcher.Request(false,menu.appearance,nullptr,ImGui::GetTime());Settle();CClick(LCenter());Settle();}
    const auto after=SnapshotFeatures();
    if(ImGui::GetIO().MetricsActiveAllocations!=allocations)
        std::fprintf(stderr,"native allocation count before %d after %d\n",allocations,ImGui::GetIO().MetricsActiveAllocations);
    for(size_t i=0;i<features.size();++i)if(features[i]!=after[i])std::fprintf(stderr,"feature %zu before %.3f after %.3f\n",i,features[i],after[i]);
    // ImGui releases stale popup/table buffers after its 60s idle threshold.
    // Retirement can reduce the total; steady launcher/menu cycles must not grow it.
    assert(ImGui::GetIO().MetricsActiveAllocations<=allocations && after==features);
    const int settledAllocations=ImGui::GetIO().MetricsActiveAllocations;
    for(int i=0;i<20;++i){launcher.Request(false,menu.appearance,nullptr,ImGui::GetTime());Settle();CClick(LCenter());Settle();}
    assert(ImGui::GetIO().MetricsActiveAllocations==settledAllocations);
    ImGui::DestroyContext();std::puts("PASS C1 actual native launcher: bounded/outside hitbox, drag without opening, 5 viewports, open/close fades, Reduced snap, route/position retention, texture reference lifecycle, passive/slider silence, actual control/nav/theme/action sound events, mute/volume, honest host-disabled settings, balanced stacks and 100 warmed cycles with stable active allocations. Original features restored unchanged.");
}
