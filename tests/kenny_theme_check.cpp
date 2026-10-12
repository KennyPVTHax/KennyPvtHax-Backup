#include "KennyAppearanceStore.h"
#include "KennyThemeBackground.h"
#include "kenny_aurora_approved.h"
#include <cassert>
#include <limits>
#include <sys/stat.h>
#include <fstream>
#include <vector>

using namespace KennyAppearance;
static int calls=0;
static bool Supply(void*,double,bool, KennyThemeBackground::ArtworkFrame& f) {
    ++calls;f={reinterpret_cast<ImTextureID>(1),1920,1080};return true;
}
int main() {
    char pattern[]="/tmp/kenny-appearance-XXXXXX";
    const char* directory=mkdtemp(pattern);assert(directory);
    Preferences p;Store store;store.Configure(directory,p);
    assert(p.theme==Theme::Aurora && store.available);
    p.theme=Theme::Anime;p.opacity=88.125f;p.compactRows=true;p.reducedMotion=true;
    p.auroraIntensity=43.5f;p.particleActivity=27;p.starsVisible=false;p.touchAttraction=false;
    p.artworkDim=82;p.artworkCover=false;p.uiSounds=false;p.uiVolume=73.25f;p.soundProfile=2;
    store.Sync(p,false);assert(access(store.path.c_str(),F_OK)!=0);
    store.Sync(p,true);assert(access(store.path.c_str(),F_OK)==0);
    struct stat st{};assert(stat(store.path.c_str(),&st)==0 && (st.st_mode&0777)==0600);
    Preferences restored;Store restart;restart.Configure(directory,restored);assert(Equal(p,restored));
    for(int i=0;i<100;++i)store.Sync(p,true);
    struct stat same{};stat(store.path.c_str(),&same);assert(st.st_ino==same.st_ino);
    // Every theme and preference round-trips; Reset defaults persists too.
    for(int t=0;t<3;++t) {
        p.theme=static_cast<Theme>(t);store.Sync(p,true);Store read;Preferences value;
        read.Configure(directory,value);assert(Equal(value,p));
    }
    p=Preferences{};store.Sync(p,true);Store reset;Preferences value;reset.Configure(directory,value);assert(Equal(value,p));
    // Read the real Phase B schema without resetting its ten preferences.
    {std::ofstream out(store.path);out<<"KennyPvtHaxAppearance 1\n2 88.125 1 1 43.5 27 0 0 82 0\n";}
    Store legacy;Preferences migrated;legacy.Configure(directory,migrated);
    assert(migrated.theme==Theme::Classic && migrated.opacity==88.125f && migrated.compactRows && migrated.reducedMotion);
    assert(migrated.auroraIntensity==43.5f && migrated.particleActivity==27 && !migrated.starsVisible && !migrated.touchAttraction);
    assert(migrated.artworkDim==82 && !migrated.artworkCover && migrated.uiSounds && migrated.uiVolume==35 && migrated.soundProfile==0);
    migrated.uiVolume=42.5f;legacy.Sync(migrated,true);Store upgraded;Preferences reread;upgraded.Configure(directory,reread);
    assert(Equal(migrated,reread));
    for(const char* corrupt:{"", "KennyPvtHaxAppearance 2\n0 97 0 0 100 100 1 1 70 1\n",
          "KennyPvtHaxAppearance 1\n8 97 0 0 100 100 1 1 70 1\n",
          "KennyPvtHaxAppearance 1\n0 nan 0 0 100 100 1 1 70 1\n",
          "KennyPvtHaxAppearance 1\n0 97 0 0 100 100 1 1 70 1\nextra",
          "KennyPvtHaxAppearance 2\n0 97 0 0 100 100 1 1 70 1\n2 35 0\n",
          "KennyPvtHaxAppearance 2\n0 97 0 0 100 100 1 1 70 1\n1 nan 0\n",
          "KennyPvtHaxAppearance 2\n0 97 0 0 100 100 1 1 70 1\n1 35 3\n",
          "KennyPvtHaxAppearance 2\n0 97 0 0 100 100 1 1 70 1\n1 35 0\nextra"}) {
        std::ofstream out(store.path);out<<corrupt;out.close();Store read;Preferences defaults;
        read.Configure(directory,defaults);assert(Equal(defaults,Preferences{}));
    }
    {std::ofstream out(store.path);out<<"KennyPvtHaxAppearance 1\n2 500 0 0 -40 900 0 0 500 0\n";}
    Store bounded;Preferences bounds;bounded.Configure(directory,bounds);
    assert(bounds.opacity==100 && bounds.auroraIntensity==0 && bounds.particleActivity==100 && bounds.artworkDim==95);
    Store missing;Preferences disabled;missing.Configure(nullptr,disabled);disabled.opacity=86;missing.Sync(disabled,true);assert(!missing.available);
    std::string nowhere=std::string(directory)+"/not-created";Store failure;Preferences failed;
    failure.Configure(nowhere.c_str(),failed);failed.theme=Theme::Classic;failure.Sync(failed,true);
    assert(std::strstr(failure.status,"failed") && !Equal(failure.observed,failed) && failure.retryPending);
    failed.opacity=std::numeric_limits<float>::quiet_NaN();Normalize(failed);assert(failed.opacity==97);
    failed.uiVolume=std::numeric_limits<float>::quiet_NaN();failed.soundProfile=99;Normalize(failed);
    assert(failed.uiVolume==35 && failed.soundProfile==2);
    unlink(store.path.c_str());rmdir(directory);
    std::puts("PASS appearance: atomic private 0600 writes, restart round-trip of every preference/theme, default reset, no idle rewrites, deferred active edits, corrupt/version/nonfinite/trailing-data fallback, clamps and unavailable/write-failure handling.");
    std::puts("PASS C1 audio preferences: all three fields round-trip, real v1 migration preserves every legacy preference, legacy audio fields persist in the current schema at the existing private path; invalid audio fields/trailing data safely rejected.");

    KennyAurora::State active;KennyAuroraApproved::State approved;
    for(int frame=0;frame<1800;++frame) {
        const bool down=frame%500<200;
        const ImVec2 canvas(1100,700),target(.5f+(frame%100)*.001f,.75f);
        active.Advance(frame,1.0f/60,canvas,down,target,false);
        approved.Advance(frame,1.0f/60,canvas,down,target,false);
        assert(active.time==approved.time && active.particleTime==approved.time && active.response==approved.response);
        for(int i=0;i<KennyAurora::StarCount;++i) {
            const auto& a=active.stars[i];const auto& b=approved.stars[i];
            assert(a.position.x==b.position.x && a.position.y==b.position.y && a.velocity.x==b.velocity.x && a.velocity.y==b.velocity.y);
        }
    }
    std::puts("PASS approved Phase A default physics: exact time/response/position/velocity equality for 1800 native-timing steps; no forces, damping, limits, seeds or curtain formulas changed.");

    using namespace KennyThemeBackground;
    Artwork art;assert(!art.current.Valid());art.SetStatic({nullptr,300,300});assert(!art.current.Valid());
    art.SetStatic({reinterpret_cast<ImTextureID>(1),300,300});assert(art.current.Valid());art.Clear();assert(!art.current.Valid());
    art.SetProvider(Supply,nullptr);art.Advance(1,.016f,true);assert(calls==1 && art.current.Valid());
    art.Advance(1,.016f,false);art.Advance(2,.016f,true);assert(calls==1 && art.time==0);
    art.Advance(3,.016f,false);assert(calls==2 && art.time>0);
    const double before=art.time;art.Advance(500,10,false);assert(art.time==before);art.Clear();assert(!art.provider && !art.current.Valid());
    art.SetProvider([](void*,double,bool,ArtworkFrame& frame){frame={reinterpret_cast<ImTextureID>(1),0,100};return true;},nullptr);
    art.Advance(1,.016f,false);assert(!art.current.Valid());
    art.SetProvider([](void*,double,bool,ArtworkFrame&){return false;},nullptr);
    art.Advance(2,.016f,false);assert(!art.current.Valid());
    ImGui::CreateContext();auto& io=ImGui::GetIO();io.IniFilename=nullptr;io.DisplaySize=ImVec2(1920,872);
    unsigned char* pixels;int w,h;io.Fonts->GetTexDataAsRGBA32(&pixels,&w,&h);
    ImGui::NewFrame();auto* draw=ImGui::GetBackgroundDrawList();
    for(bool cover:{false,true})for(ImVec2 image:{ImVec2(1080,1920),ImVec2(1920,1080),ImVec2(1100,700)}) {
        draw->_ResetForNewFrame();Preferences pref;pref.artworkCover=cover;
        DrawArtwork(draw,ImVec2(0,0),ImVec2(1100,700),34,{reinterpret_cast<ImTextureID>(1),int(image.x),int(image.y)},pref);
        assert(draw->VtxBuffer.Size==625 && draw->IdxBuffer.Size==3456);
        for(const auto& v:draw->VtxBuffer) {
            assert(KennyEffects::Contains(v.pos,ImVec2(1100,700),34));
            assert(v.uv.x>=-1e-6 && v.uv.y>=-1e-6 && v.uv.x<=1.000001 && v.uv.y<=1.000001);
        }
    }
    for(float dim:{35.0f,95.0f}) {
        draw->_ResetForNewFrame();Preferences pref;pref.artworkDim=dim;
        DrawArtwork(draw,ImVec2(0,0),ImVec2(1100,700),34,{reinterpret_cast<ImTextureID>(1),1920,1080},pref);
        for(const auto& v:draw->VtxBuffer) assert(v.col==ImGui::GetColorU32(ImVec4(1,1,1,1-dim*.01f)));
    }
    draw->_ResetForNewFrame();
    KennyAurora::Draw(draw,ImVec2(0,0),ImVec2(1100,700),1,34,active,false,100,174);
    const std::vector<ImDrawVert> vertices(draw->VtxBuffer.begin(),draw->VtxBuffer.end());
    const std::vector<ImDrawIdx> indices(draw->IdxBuffer.begin(),draw->IdxBuffer.end());
    draw->_ResetForNewFrame();
    KennyAuroraApproved::Draw(draw,ImVec2(0,0),ImVec2(1100,700),1,34,approved,false,100,174);
    assert(vertices.size()==size_t(draw->VtxBuffer.Size) && indices.size()==size_t(draw->IdxBuffer.Size));
    assert(std::memcmp(vertices.data(),draw->VtxBuffer.Data,vertices.size()*sizeof(ImDrawVert))==0);
    assert(std::memcmp(indices.data(),draw->IdxBuffer.Data,indices.size()*sizeof(ImDrawIdx))==0);
    std::puts("PASS approved Phase A default draw vertices/UVs/colors/indices remain byte-identical to commit 58cbf6c.");
    ImGui::EndFrame();ImGui::DestroyContext();
    std::puts("PASS artwork: safe missing/invalid/static/provider frames, same-frame idempotence, Reduced frame hold, inactive-gap no catch-up, clearing texture ownership; portrait/landscape Cover/Contain rounded geometry and UVs. Test texture handles are diagnostic only; no artwork is supplied or generated.");
}
