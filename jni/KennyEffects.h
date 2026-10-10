#pragma once
#include <array>
#include <cmath>
#include "ClaudeTheme.h"

namespace KennyEffects {
constexpr int ParticleCount = 48;
constexpr int Columns = 24, Rows = 24, CornerRows = 6;
struct State {
    double time = 0;
    float reveal = 0;
    int frame = -2;
    bool Advance(int nextFrame, float dt) {
        const bool resumed = frame != nextFrame-1;
        if (resumed) reveal = 0;
        else time = std::fmod(time + KennyMotion::Delta(dt), 4096.0);
        reveal = KennyMotion::Step(reveal, 1.0f, 12.0f, dt);
        frame = nextFrame;
        return resumed;
    }
};
// Insets include the halo radius and antialiasing fringe. All generated
// vertices lie in a convex rounded rectangle; triangles cannot escape it.
inline bool Contains(ImVec2 p, ImVec2 size, float radius, float inset = 0) {
    const float x = p.x-inset, y = p.y-inset;
    const float w = size.x-2*inset, h = size.y-2*inset;
    if (x < 0 || y < 0 || x > w || y > h) return false;
    const float r = std::max(0.0f, std::min(radius-inset, std::min(w,h)*0.5f));
    const float dx = x-std::clamp(x,r,w-r), dy = y-std::clamp(y,r,h-r);
    return dx*dx+dy*dy <= r*r+0.001f;
}
inline ImVec2 MeshPoint(int x, int y, ImVec2 size, float radius) {
    // A subpixel inset keeps float rounding and the native edge's AA fringe
    // from putting bloom vertices just beyond the rounded boundary.
    constexpr float inset = 0.25f;
    size.x -= 2*inset; size.y -= 2*inset;
    radius = std::max(0.0f,radius-inset);
    const float r = std::min(radius, std::min(size.x,size.y)*0.5f);
    // Denser sampling on each quarter-circle avoids a visible diagonal cut
    // through the corner bloom while keeping the mesh strictly inside it.
    float yy;
    if (y <= CornerRows) yy = r*(1-std::cos(1.570796327f*y/CornerRows));
    else if (y >= Rows-CornerRows) yy = size.y-r*(1-std::cos(1.570796327f*(Rows-y)/CornerRows));
    else yy = r+(size.y-2*r)*(y-CornerRows)/(Rows-2*CornerRows);
    const float dy = yy < r ? r-yy : yy > size.y-r ? yy-(size.y-r) : 0;
    const float edge = r-std::sqrt(std::max(0.0f,r*r-dy*dy));
    return ImVec2(inset+edge + (size.x-2*edge)*x/Columns, inset+yy);
}
constexpr unsigned Hash(unsigned x) { x ^= x >> 16; x *= 0x7feb352du; x ^= x >> 15; x *= 0x846ca68bu; return x ^ (x >> 16); }
constexpr float Unit(unsigned x) { return (Hash(x) & 65535u)/65535.0f; }
struct Seed { float x,y,speed,radius,phase; };
constexpr std::array<Seed, ParticleCount> Seeds() {
    std::array<Seed, ParticleCount> seeds{};
    for (int i=0;i<ParticleCount;++i)
        seeds[i] = {Unit(i*5+1), Unit(i*5+2), 0.002f+Unit(i*5+3)*0.003f,
                    0.65f+Unit(i*5+4)*0.65f, Unit(i*5+5)*6.2831853f};
    return seeds;
}
inline constexpr auto particles = Seeds();
inline ImVec2 Particle(const Seed& seed, ImVec2 size, double time) {
    const float t = static_cast<float>(time);
    const float y = seed.y - t*seed.speed;
    return ImVec2((seed.x+std::sin(t*0.12f+seed.phase)*0.007f)*size.x,
                  (y-std::floor(y))*size.y);
}
inline float Bloom(ImVec2 p, ImVec2 center, float rx, float ry) {
    const float x=(p.x-center.x)/rx, y=(p.y-center.y)/ry;
    const float v=std::max(0.0f,1.0f-x*x-y*y);
    return v*v*v;
}
inline void Draw(ImDrawList* draw, ImVec2 origin, ImVec2 size, float scale,
                 float radius, const State& state) {
    const float t = static_cast<float>(state.time);
    const float strength = 0.35f+0.65f*state.reveal;
    const ImVec2 left(size.x*(0.14f+0.035f*std::sin(t*0.11f)),size.y*0.08f);
    const ImVec2 right(size.x*0.91f,size.y*(0.70f+0.06f*std::sin(t*0.09f)));
    draw->PushClipRect(origin, ImVec2(origin.x+size.x,origin.y+size.y),true);
    // Fixed tessellation, using the existing atlas white pixel; no blur passes,
    // textures, heap containers, or resource creation in this effect.
    const unsigned base=draw->_VtxCurrentIdx;
    draw->PrimReserve(Columns*Rows*6,(Columns+1)*(Rows+1));
    const ImVec2 uv=ImGui::GetFontTexUvWhitePixel();
    for (int y=0;y<=Rows;++y) {
        const ImVec2 edge=MeshPoint(0,y,size,radius);
        for(int x=0;x<=Columns;++x) {
            const ImVec2 p(edge.x+(size.x-2*edge.x)*x/Columns,edge.y);
            const float light=0.32f*Bloom(p,left,size.x*0.56f,size.y*0.70f)
                             +0.21f*Bloom(p,right,size.x*0.46f,size.y*0.65f);
            draw->PrimWriteVtx(ImVec2(origin.x+p.x,origin.y+p.y),uv,
                               ImGui::GetColorU32(Claude::Hex(0xA93646,light*strength)));
        }
    }
    for (int y=0;y<Rows;++y) for(int x=0;x<Columns;++x) {
        const unsigned a=base+y*(Columns+1)+x,b=a+1,c=a+Columns+1,d=c+1;
        for(unsigned index:{a,b,c,b,d,c})draw->PrimWriteIdx(static_cast<ImDrawIdx>(index));
    }
    for (int i=0;i<ParticleCount;++i) {
        const auto& seed=particles[i];
        const ImVec2 p=Particle(seed,size,state.time);
        const float r=std::max(0.55f,seed.radius*scale);
        const float halo=r+2*scale;
        if (!Contains(p,size,radius,halo+1)) continue;
        const ImVec2 center(origin.x+p.x,origin.y+p.y);
        const float alpha=(0.24f+0.13f*(0.5f+0.5f*std::sin(t*0.30f+seed.phase)))*strength;
        draw->AddCircleFilled(center,halo,ImGui::GetColorU32(Claude::Hex(0xFF5A5F,alpha*0.12f)),8);
        draw->AddCircleFilled(center,r,ImGui::GetColorU32(Claude::Hex(i%4 ? 0xCF8C95 : 0xF5F2F2,alpha)),8);
    }
    // Inward edge illumination leaves overlay pixels outside the shell alone.
    for(int i=0;i<3;++i) {
        const float inset=std::max(2.0f,2*scale)+i*2*scale;
        draw->AddRect(ImVec2(origin.x+inset,origin.y+inset),
                      ImVec2(origin.x+size.x-inset,origin.y+size.y-inset),
                      ImGui::GetColorU32(Claude::Hex(0xE63946,(0.09f-i*0.025f)*strength)),
                      std::max(0.0f,radius-inset),0,1.0f);
    }
    draw->PopClipRect();
}
} // namespace KennyEffects
