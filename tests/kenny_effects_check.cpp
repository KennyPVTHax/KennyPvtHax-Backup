// SDK-independent checks against the production ImGui effect/motion headers.
// Build instructions are in tests/README.md. Assertions must remain enabled.
#include "KennyEffects.h"
#include <cassert>
#include <cstdio>
#include <limits>

int main() {
    using namespace KennyMotion;
    // Exponential interpolation agrees across normal frame rates, is finite,
    // never overshoots, and tolerates malformed or suspended frame timing.
    float results[3] = {};
    int k=0;
    for(int fps:{30,60,120}) {
        float value=0;
        for(int i=0;i<fps;++i)value=Step(value,1,8,1.0f/fps);
        results[k++]=value;
    }
    assert(std::abs(results[0]-results[2])<0.00001f);
    assert(Delta(-1)==0 && Delta(std::numeric_limits<float>::quiet_NaN())==0);
    assert(Delta(std::numeric_limits<float>::infinity())==0 && Delta(5)==0.1f);
    float indicator=0;
    for(int i=0;i<2000;++i) {
        const float target=static_cast<float>((i*3)%5);
        const float next=Step(indicator,target,18,i%3 ? 1.0f/60 : 0.08f);
        assert(std::isfinite(next) && next>=std::min(indicator,target) && next<=std::max(indicator,target));
        indicator=next;
    }
    KennyEffects::State state;
    assert(state.Advance(1,1.0f/60));
    assert(!state.Advance(2,1.0f/60));
    const double before=state.time;
    // A gap represents hidden frames: no elapsed hidden time is simulated.
    assert(state.Advance(4000,5) && state.time==before);
    assert(state.reveal>0 && state.reveal<1);

    ImGui::CreateContext();
    auto& io=ImGui::GetIO(); io.IniFilename=nullptr; io.LogFilename=nullptr;
    io.DisplaySize=ImVec2(1920,872);io.DeltaTime=1.0f/60;
    unsigned char* pixels;int width,height;io.Fonts->GetTexDataAsRGBA32(&pixels,&width,&height);
    // The polished floating-toggle wrapper retains its native 84x36 hitbox,
    // release activation, and disabled input behavior.
    int presses=0;bool disabled=false;
    auto buttonFrame=[&](bool down) {
        io.MousePos=ImVec2(50,48);io.MouseDown[0]=down;
        ImGui::NewFrame();
        ImGui::SetNextWindowPos(ImVec2(20,20));
        ImGui::Begin("##button-test",nullptr,ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoSavedSettings);
        ImGui::BeginDisabled(disabled);
        if(Claude::PrimaryButton("Menu",ImVec2(84,36)))++presses;
        const ImVec2 a=ImGui::GetItemRectMin(),b=ImGui::GetItemRectMax();
        assert(b.x-a.x==84 && b.y-a.y==36);
        ImGui::EndDisabled();ImGui::End();ImGui::Render();
        assert(ImGui::GetStyle().Alpha==1);
    };
    buttonFrame(false);buttonFrame(false);buttonFrame(true);assert(presses==0);
    buttonFrame(false);assert(presses==1);
    disabled=true;buttonFrame(true);buttonFrame(false);assert(presses==1);
    io.MousePos=ImVec2(-100,-100);
    ImGui::NewFrame();
    assert(Sample(101,3,0)==0);
    assert(Sample(101,3,1,18,true)==1); // Immediate active-input snap.
    for(unsigned id=1;id<10000;++id)assert(std::isfinite(Sample(id,7,0.5f)));
    static_assert(sizeof(cache.entries)==Capacity*sizeof(Entry),"Animation storage must remain fixed");
    ImGui::EndFrame();
    ImGui::NewFrame();assert(Sample(55555,3,0)==0);ImGui::EndFrame();
    ImGui::NewFrame();assert(Sample(55555,3,1)>0 && Sample(55555,3,1)<1);ImGui::EndFrame();
    ImGui::NewFrame();ImGui::EndFrame(); // Not submitted (hidden/clipped).
    ImGui::NewFrame();assert(Sample(55555,3,0.7f)==0.7f);ImGui::EndFrame();

    // Inspect every actual generated vertex, including particle halos and
    // antialiasing fringes, against the rounded shell in five viewport scales.
    {
    ImDrawList draw(ImGui::GetDrawListSharedData());
    unsigned maximumVertices=0, maximumIndices=0;
    for (float scale:{0.55f,0.62f,0.83f,1.0f,1.24f}) {
        const ImVec2 size(1133*scale,715*scale), origin(70,40);
        const float radius=34*scale;
        for(int y=0;y<=KennyEffects::Rows;++y)for(int x=0;x<=KennyEffects::Columns;++x)
            assert(KennyEffects::Contains(KennyEffects::MeshPoint(x,y,size,radius),size,radius));
        for(int sample=0;sample<100;++sample) {
            state.time=sample*41.37;state.reveal=1;
            draw._ResetForNewFrame();draw.PushTextureID(io.Fonts->TexID);
            draw.PushClipRectFullScreen();
            KennyEffects::Draw(&draw,origin,size,scale,radius,state);
            for(const auto& v:draw.VtxBuffer)
                assert(KennyEffects::Contains(ImVec2(v.pos.x-origin.x,v.pos.y-origin.y),size,radius));
            maximumVertices=std::max(maximumVertices,static_cast<unsigned>(draw.VtxBuffer.Size));
            maximumIndices=std::max(maximumIndices,static_cast<unsigned>(draw.IdxBuffer.Size));
        }
    }
    // Warmed draw buffers remain at a fixed high-water mark over 1000 frames.
    // The effect itself has no heap state; standard ImGui geometry is reused.
    const int allocations=io.MetricsActiveAllocations;
    const int vCapacity=draw.VtxBuffer.Capacity, iCapacity=draw.IdxBuffer.Capacity;
    for(int i=0;i<1000;++i) {
        draw._ResetForNewFrame();draw.PushTextureID(io.Fonts->TexID);draw.PushClipRectFullScreen();
        state.time=i/60.0;state.reveal=1;
        KennyEffects::Draw(&draw,ImVec2(70,40),ImVec2(1133,715),1,34,state);
        assert(draw.VtxBuffer.Capacity==vCapacity && draw.IdxBuffer.Capacity==iCapacity);
        assert(io.MetricsActiveAllocations==allocations);
    }
    std::printf("PASS native toggle hitbox/release/disabled input, effect math, hidden-time pause, bounded cache, rapid targets, rounded geometry (500 samples), warmed allocation stability (1000 frames); max effect vertices=%u indices=%u, cache=%zu bytes.\n",
                maximumVertices,maximumIndices,sizeof(cache.entries));
    }
    ImGui::DestroyContext();
}
