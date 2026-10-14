#include "KennyElectricStarfield.h"
#include "KennyAppearanceStore.h"
#include <cassert>
#include <chrono>
#include <cstdio>
#include <fstream>
#include <limits>
#include <vector>
#include <cstring>

int main(){
    using namespace KennyElectric;using KennyAppearance::Preferences;
    Preferences p;p.theme=KennyAppearance::Theme::Classic;
    double times[4]{};int n=0;
    for(int fps:{30,60,90,120}){State s;s.Advance(0,1.f/fps,p);for(int i=1;i<=fps*10;++i)s.Advance(i,1.f/fps,p);times[n++]=s.time;}
    for(double t:times)assert(std::abs(t-10)<.00001);
    State state;state.Advance(1,.016f,p);assert(state.time==0);state.Advance(2,.016f,p);const auto before=state.time;
    state.Advance(2,10,p);assert(state.time==before);state.Advance(900,10,p);assert(state.time==before);
    state.Advance(901,std::numeric_limits<float>::quiet_NaN(),p);assert(state.time==before);
    state.Advance(902,-1,p);assert(state.time==before);state.Advance(903,10,p);assert(std::abs(state.time-before-.1)<1e-6);
    p.electricReducedMotion=true;const auto held=state.time;for(int i=904;i<940;++i)state.Advance(i,.016f,p);assert(state.time==held);
    p.electricReducedMotion=false;p.electricSpeed=0;state.Advance(940,.016f,p);assert(state.time==held);
    p.electricSpeed=50;p.electricStarfield=false;state.Advance(941,.016f,p);assert(state.time==held);
    p.electricStarfield=true;
    char dir[]="/tmp/kenny-electric-XXXXXX";assert(mkdtemp(dir));KennyAppearance::Store store;store.Configure(dir,p);
    p.electricDensity=2;p.electricLightning=83.2f;p.electricSparkle=11.5f;p.electricSpeed=32.75f;p.electricPulses=false;p.electricReducedMotion=true;
    store.Sync(p,true);Preferences restored;KennyAppearance::Store restart;restart.Configure(dir,restored);assert(KennyAppearance::Equal(p,restored));
    const char* legacy="KennyPvtHaxAppearance 4\n2 89 1 0 52 23 0 1 78 0\n0 21 2\nhighschool_dxd_rias supplied_event_clips character.png 1 83 0\n0 1\n";
    {std::ofstream f(store.path);f<<legacy;}
    Preferences old;KennyAppearance::Store migration;migration.Configure(dir,old);assert(old.theme==KennyAppearance::Theme::Classic&&old.opacity==89&&old.voicePack=="supplied_event_clips"&&!old.artworkVisible&&old.controlVoiceFeedback);
    assert(old.electricStarfield&&old.electricDensity==1&&old.electricLightning==45&&old.electricPulses&&!old.electricReducedMotion);
    std::string v5=legacy;v5.replace(v5.find('4'),1,"5");
    for(const char* bad:{"1 1 nan 55 50 1 0\n","2 1 45 55 50 1 0\n","1 1 45 55 50 1 0\ntrailing",""}){
        {std::ofstream f(store.path);f<<v5<<bad;}Preferences badPrefs;KennyAppearance::Store load;load.Configure(dir,badPrefs);
        assert(KennyAppearance::Equal(badPrefs,old));assert(std::strstr(load.status,"Classic effects preferences invalid"));
    }
    {std::ofstream f(store.path);f<<v5<<"1 99 200 -9 200 1 0\n";}
    Preferences clamps;KennyAppearance::Store load;load.Configure(dir,clamps);assert(clamps.electricDensity==2&&clamps.electricLightning==100&&clamps.electricSparkle==0&&clamps.electricSpeed==100);
    unlink(store.path.c_str());rmdir(dir);
    ImGui::CreateContext();auto& io=ImGui::GetIO();io.IniFilename=nullptr;io.LogFilename=nullptr;io.DisplaySize=ImVec2(1920,872);
    unsigned char* pixels;int w,h;io.Fonts->GetTexDataAsRGBA32(&pixels,&w,&h);ImGui::NewFrame();
    ImDrawList draw(ImGui::GetDrawListSharedData());p=Preferences{};p.theme=KennyAppearance::Theme::Classic;
    unsigned maxV=0,maxI=0;
    for(float scale:{.55f,.83f,1.f,1.5f})for(bool reduced:{false,true})for(int sample=0;sample<60;++sample){
        p.electricDensity=sample%3;p.electricReducedMotion=reduced;p.electricLightning=sample%2?100:45;
        const ImVec2 origin(13,29),size(1133*scale,715*scale);state.time=sample*1.337;
        draw._ResetForNewFrame();draw.PushTextureID(io.Fonts->TexID);draw.PushClipRectFullScreen();
        Draw(&draw,origin,size,scale,34*scale,state,p,100*scale,174*scale);
        for(const auto& v:draw.VtxBuffer)assert(std::isfinite(v.pos.x+v.pos.y)&&KennyEffects::Contains(ImVec2(v.pos.x-origin.x,v.pos.y-origin.y),size,34*scale));
        for(int i=10;i<14;++i){const auto& parent=state.paths[(i-10)*2][Segments/2];const auto& root=state.paths[i][0];assert(std::hypot(root.x-parent.x,root.y-parent.y)<.01f);}
        maxV=std::max(maxV,unsigned(draw.VtxBuffer.Size));maxI=std::max(maxI,unsigned(draw.IdxBuffer.Size));
    }
    assert(maxV<10000&&maxI<30000);
    p=Preferences{};p.electricDensity=2;const ImVec2 size(1133,715);
    // Warm maximum geometry before counting native ImGui heap allocations.
    for(int sample=0;sample<400;++sample){state.time=sample*.15;draw._ResetForNewFrame();draw.PushTextureID(io.Fonts->TexID);draw.PushClipRectFullScreen();Draw(&draw,ImVec2(0,0),size,1,34,state,p,100,174);}
    const int allocations=io.MetricsActiveAllocations,vc=draw.VtxBuffer.Capacity,ic=draw.IdxBuffer.Capacity;
    std::array<double,1000> costs{};
    for(int i=0;i<1000;++i){state.time=i*.027;draw._ResetForNewFrame();draw.PushTextureID(io.Fonts->TexID);draw.PushClipRectFullScreen();
        const auto start=std::chrono::steady_clock::now();Draw(&draw,ImVec2(0,0),size,1,34,state,p,100,174);
        costs[i]=std::chrono::duration<double,std::micro>(std::chrono::steady_clock::now()-start).count();
        assert(allocations==io.MetricsActiveAllocations&&vc==draw.VtxBuffer.Capacity&&ic==draw.IdxBuffer.Capacity);
    }
    std::sort(costs.begin(),costs.end());std::printf("MEASURE host high density: p50 %.2f us; p95 %.2f us; maximum geometry %u vertices / %u indices. Android performance unverified.\n",costs[500],costs[950],maxV,maxI);
    p.electricReducedMotion=true;state.time=4.4;
    draw._ResetForNewFrame();draw.PushTextureID(io.Fonts->TexID);draw.PushClipRectFullScreen();Draw(&draw,ImVec2(0,0),size,1,34,state,p,100,174);
    const std::vector<ImDrawVert> frozen(draw.VtxBuffer.begin(),draw.VtxBuffer.end());
    state.Advance(2000,10,p);draw._ResetForNewFrame();draw.PushTextureID(io.Fonts->TexID);draw.PushClipRectFullScreen();Draw(&draw,ImVec2(0,0),size,1,34,state,p,100,174);
    assert(frozen.size()==size_t(draw.VtxBuffer.Size)&&!std::memcmp(frozen.data(),draw.VtxBuffer.Data,frozen.size()*sizeof(ImDrawVert)));
    p.electricStarfield=false;draw._ResetForNewFrame();draw.PushTextureID(io.Fonts->TexID);draw.PushClipRectFullScreen();Draw(&draw,ImVec2(0,0),size,1,34,state,p,100,174);assert(draw.VtxBuffer.Size==0);
    for(int slot=0;slot<MaxPulses;++slot)for(int i=0;i<3000;++i){const auto energy=Energy(i*.017,slot);assert(energy.path>=0&&energy.path<10&&energy.alpha>=0&&energy.alpha<=1);}
    // Adjacent times preserve coherent shape; no frame-wise random redraw.
    state.time=3;Prepare(state,size,34,1);const auto paths=state.paths;state.time+=1.0/120;Prepare(state,size,34,1);
    for(int j=0;j<Filaments;++j)for(int k=0;k<=Segments;++k)assert(std::hypot(paths[j][k].x-state.paths[j][k].x,paths[j][k].y-state.paths[j][k].y)<.5);
    ImGui::EndFrame();ImGui::DestroyContext();
    std::puts("PASS electric: 30/60/90/120 timing, stalls/hidden gaps, finite inputs, pause/reduced/off, bounded coherent connected paths, pulse bounds, rounded clipping, stable warmed allocations, schema 4 migration/5 roundtrip/corruption/clamps.");
}
