// Phase A physics and actual native draw-data checks. No SDK or mock renderer.
#include "KennyAurora.h"
#include <cassert>
#include <cstdio>
#include <limits>

namespace {
const ImVec2 canvas(1132.8f,715.04f);
float Distance(ImVec2 a,ImVec2 b) { return std::hypot((a.x-b.x)*canvas.x/canvas.y,a.y-b.y); }
void Finite(const KennyAurora::State& s) {
    assert(std::isfinite(s.time) && s.response>=0 && s.response<=1.00001f);
    assert(s.accumulator>=0 && s.accumulator<KennyAurora::FixedStep+1e-6f);
    for(const auto& star:s.stars) {
        assert(std::isfinite(star.velocity.x) && std::isfinite(star.velocity.y));
        assert(star.position.x>=.065f && star.position.x<=.935f);
        assert(star.position.y>=.065f && star.position.y<=.935f);
        assert(Distance(star.velocity,ImVec2(0,0))<=.28001f);
    }
}
KennyAurora::State Run(int fps) {
    KennyAurora::State s;
    s.Advance(0,0,canvas,false,ImVec2(.5f,.74f),false);
    for(int frame=1;frame<=fps*6;++frame) {
        const bool down=frame<=fps*3;
        const ImVec2 target(frame<=fps*2 ? .5f : .62f,.74f);
        s.Advance(frame,1.0f/fps,canvas,down,target,false); Finite(s);
    }
    return s;
}
}
int main() {
    static_assert(KennyAurora::StarCount==40,"strict bounded particle budget");
    KennyAurora::State s, copy;
    s.Initialize();copy.Initialize();
    for(int i=0;i<KennyAurora::StarCount;++i) {
        assert(s.stars[i].position.x==copy.stars[i].position.x);
        assert(s.stars[i].position.y==copy.stars[i].position.y);
        assert(s.stars[i].radius==copy.stars[i].radius);
    }
    const auto a=Run(30),b=Run(60),c=Run(120);
    for(int i=0;i<KennyAurora::StarCount;++i) {
        assert(Distance(a.stars[i].position,c.stars[i].position)<.006f);
        assert(Distance(b.stars[i].position,c.stars[i].position)<.003f);
    }
    int frame=0;
    s.Advance(frame++,0,canvas,false,ImVec2(.5f,.74f),false);
    std::array<bool,KennyAurora::StarCount> near{};
    float before=0,after=0; int count=0;
    for(int i=0;i<KennyAurora::StarCount;++i) {
        near[i]=Distance(s.stars[i].position,ImVec2(.5f,.74f))<.30f;
        if(near[i]) {before+=Distance(s.stars[i].position,ImVec2(.5f,.74f));++count;}
    }
    assert(count>=3);
    for(int i=0;i<240;++i) s.Advance(frame++,1.0f/60,canvas,true,ImVec2(.5f,.74f),false);
    for(int i=0;i<KennyAurora::StarCount;++i) if(near[i]) after+=Distance(s.stars[i].position,ImVec2(.5f,.74f));
    assert(after<before*.75f);
    const auto held=s;
    // Initial release retains inertia, with no positional reset/teleport.
    s.Advance(frame++,1.0f/60,canvas,false,ImVec2(.5f,.74f),false);
    for(int i=0;i<KennyAurora::StarCount;++i) assert(Distance(s.stars[i].position,held.stars[i].position)<=.28f/60+1e-6f);
    for(int i=0;i<900;++i) s.Advance(frame++,1.0f/60,canvas,false,ImVec2(.5f,.74f),false);
    for(int i=0;i<KennyAurora::StarCount;++i) assert(Distance(s.stars[i].position,KennyAurora::State::Home(i,s.time))<.003f);
    assert(s.response<1e-5f);
    // Frame gaps freeze, malformed/stalled dt never runs unbounded substeps.
    const double previous=s.time;
    s.Advance(frame+100,.1f,canvas,true,ImVec2(.5f,.74f),false);assert(s.time==previous);
    frame+=101;
    for(float dt:{-1.0f,0.0f,std::numeric_limits<float>::quiet_NaN(),std::numeric_limits<float>::infinity(),100.0f}) {
        const double time=s.time;
        s.Advance(frame++,dt,canvas,true,ImVec2(.5f,.74f),false);
        assert(s.time-time<=.100001);Finite(s);
    }
    auto reduced=s;
    for(int i=0;i<120;++i) reduced.Advance(frame++,1.0f/60,canvas,true,ImVec2(.8f,.8f),true);
    assert(reduced.time==s.time && reduced.response==0);
    for(int i=0;i<KennyAurora::StarCount;++i) assert(Distance(reduced.stars[i].position,s.stars[i].position)==0);
    // Extreme moves, edge touches and changing dt remain finite and bounded.
    for(int i=0;i<20000;++i) {
        const auto old=s;
        const float dt=i%37 ? 1.0f/120 : .1f;
        s.Advance(frame++,dt,canvas,i%311<190,ImVec2(i%193<100 ? .02f : .98f,i%151<80 ? .02f : .98f),false);
        Finite(s);
        for(int j=0;j<KennyAurora::StarCount;++j) assert(Distance(s.stars[j].position,old.stars[j].position)<=.28f*dt+1e-5f);
    }
    const auto same=s; s.Advance(frame-1,.1f,canvas,true,ImVec2(.2f,.2f),false);assert(s.time==same.time);
    // Noise is temporally continuous even after long sessions; no clock reset.
    for(double t:{0.0,4096.0,1e9}) for(int layer=0;layer<3;++layer) {
        const auto first=KennyAurora::Curtain(.4f,t,layer),next=KennyAurora::Curtain(.4f,t+.0001,layer);
        assert(std::abs(first.lower-next.lower)<.0001f);
    }
    ImGui::CreateContext();auto& io=ImGui::GetIO();io.IniFilename=nullptr;io.LogFilename=nullptr;
    unsigned char* pixels;int w,h;io.Fonts->GetTexDataAsRGBA32(&pixels,&w,&h);
    io.DisplaySize=ImVec2(1920,872);ImGui::NewFrame();
    {
        ImDrawList draw(ImGui::GetDrawListSharedData());
        unsigned maxVertices=0,maxIndices=0;
        for(float scale:{.55f,.62f,.83f,1.0f,1.24f}) for(bool reducedMode:{false,true}) for(int sample=0;sample<60;++sample) {
            s.time=sample*31.71;s.response=sample%3*.5f;
            const ImVec2 size(1133*scale,715*scale),origin(70,40);
            for(const auto& star:s.stars) {
                const float halo=std::max(.55f,star.radius*scale)+2.5f*scale+1;
                assert(KennyEffects::Contains(ImVec2(star.position.x*size.x,star.position.y*size.y),size,34*scale,halo));
            }
            draw._ResetForNewFrame();draw.PushTextureID(io.Fonts->TexID);draw.PushClipRectFullScreen();
            KennyAurora::Draw(&draw,origin,size,scale,34*scale,s,reducedMode,100*scale,174*scale);
            for(const auto& v:draw.VtxBuffer) assert(KennyEffects::Contains(ImVec2(v.pos.x-origin.x,v.pos.y-origin.y),size,34*scale));
            maxVertices=std::max(maxVertices,static_cast<unsigned>(draw.VtxBuffer.Size));
            maxIndices=std::max(maxIndices,static_cast<unsigned>(draw.IdxBuffer.Size));
        }
        const int allocations=io.MetricsActiveAllocations,vCapacity=draw.VtxBuffer.Capacity,iCapacity=draw.IdxBuffer.Capacity;
        for(int i=0;i<1000;++i) {
            s.time=i/60.0;s.response=i%2;
            draw._ResetForNewFrame();draw.PushTextureID(io.Fonts->TexID);draw.PushClipRectFullScreen();
            KennyAurora::Draw(&draw,ImVec2(70,40),canvas,1,34,s,false,100,174);
            assert(io.MetricsActiveAllocations==allocations && draw.VtxBuffer.Capacity==vCapacity && draw.IdxBuffer.Capacity==iCapacity);
        }
        std::printf("PASS seeded 40-star physics, attraction %.3f->%.3f mean distance (%d nearby), release/home recovery, 30/60/120 Hz agreement, 20000 variable-dt edge/drag steps, reduced/hidden/idempotent timing, long-session continuity, 600 actual rounded geometry samples, 1000 warmed allocation frames; max %u vertices/%u indices; fixed state %zu bytes.\n",before/count,after/count,count,maxVertices,maxIndices,sizeof(s));
    }
    ImGui::EndFrame();ImGui::DestroyContext();
}
