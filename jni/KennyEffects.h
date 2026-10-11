#pragma once
#include <array>
#include <cmath>
#include "ClaudeTheme.h"

namespace KennyEffects {
constexpr int ParticleCount = 40, StationaryCount = 24, EmberCount = 12;
constexpr int Columns = 24, Rows = 24, CornerRows = 6;
struct State {
    double time = 0;
    float reveal = 0;
    int frame = -2;
    bool Advance(int nextFrame, float dt, bool reduced = false) {
        if(nextFrame==frame)return false;
        const bool resumed = frame != nextFrame-1;
        if (resumed) reveal = 0;
        else if(!reduced) time += KennyMotion::Delta(dt);
        // Double precision avoids a periodic global-clock reset/visible jump.
        reveal = reduced ? 1.0f : KennyMotion::Step(reveal, 1.0f, 12.0f, dt);
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
        seeds[i] = {Unit(i*5+1), Unit(i*5+2), 0.0015f+Unit(i*5+3)*0.002f,
                    0.65f+Unit(i*5+4)*0.65f, Unit(i*5+5)*6.2831853f};
    return seeds;
}
inline constexpr auto particles = Seeds();
inline ImVec2 Particle(const Seed& seed, ImVec2 size, double time) {
    const float y = seed.y - static_cast<float>(std::fmod(time*seed.speed,1.0));
    return ImVec2((seed.x+static_cast<float>(std::sin(time*0.12+seed.phase))*0.004f)*size.x,
                  (y-std::floor(y))*size.y);
}
inline float Bloom(ImVec2 p, ImVec2 center, float rx, float ry) {
    const float x=(p.x-center.x)/rx, y=(p.y-center.y)/ry;
    const float v=std::max(0.0f,1.0f-x*x-y*y);
    return v*v*v;
}
inline float Spark(const Seed& seed, double time) {
    const float age=static_cast<float>(std::fmod(time+seed.phase*3,17.0));
    const float v=std::max(0.0f,1.0f-std::abs(age-6.0f)/0.8f);
    return v*v*(3-2*v);
}
struct Lighting { ImVec2 crown,eclipse,shade,farGlow; float breath; };
inline Lighting Lights(ImVec2 size, double time) {
    const float sway=static_cast<float>(std::sin(time*0.31)*0.024+std::sin(time*0.19)*0.010);
    const ImVec2 eclipse(size.x*(0.83f-sway*0.5f),size.y*0.91f);
    return {ImVec2(size.x*(0.10f+sway),size.y*0.06f),eclipse,
            ImVec2(eclipse.x+size.x*0.07f,eclipse.y-size.y*0.055f),ImVec2(size.x*0.95f,size.y*0.26f),
            0.88f+0.12f*static_cast<float>(std::sin(time*0.27))};
}
inline ImVec4 Material(ImVec2 p, ImVec2 size, const Lighting& lights, float header, float content) {
    const float corona=std::clamp((Bloom(p,lights.eclipse,size.x*0.36f,size.y*0.53f)
        -1.4f*Bloom(p,lights.shade,size.x*0.30f,size.y*0.47f))*2.2f,0.0f,1.0f);
    const float crownLight=Bloom(p,lights.crown,size.x*0.39f,size.y*0.62f)*lights.breath;
    const float farLight=Bloom(p,lights.farGlow,size.x*0.28f,size.y*0.40f)*0.26f;
    ImVec4 material=Claude::Hex(0x100B0F,0.20f);
    material=KennyMotion::Mix(material,Claude::Hex(0x6F2437,0.46f),crownLight*0.72f);
    material=KennyMotion::Mix(material,Claude::Hex(0x963B4C,0.38f),corona*0.85f);
    material=KennyMotion::Mix(material,Claude::Hex(0x69404A,0.38f),farLight);
    // A graphite header shelf and quieter secondary band separate chrome
    // from content, while keeping illumination integrated across the shell.
    const float headerBand=std::clamp((header+10-p.y)/20,0.0f,1.0f);
    const float secondaryBand=std::clamp((p.y-header+5)/10,0.0f,1.0f)*
        std::clamp((content+5-p.y)/10,0.0f,1.0f);
    material=KennyMotion::Mix(material,Claude::Hex(0x211A20,0.48f),headerBand*0.45f);
    material=KennyMotion::Mix(material,Claude::Hex(0x100B0F,0.35f),secondaryBand*0.38f);
    return material;
}
inline void Glint(ImDrawList* draw, ImVec2 origin, ImVec2 size, float scale, double time) {
    const float age=static_cast<float>(std::fmod(time,17.0));
    if(age<5 || age>7)return;
    const float progress=(age-5)*0.5f;
    const float pulse=std::sin(progress*3.141592654f);
    const float width=54*scale, x=origin.x+size.x*(0.35f+progress*0.28f);
    KennyPaint::Seam(draw,ImVec2(x,origin.y+2.5f),width,
                      Claude::Hex(0xF4C8D0,pulse*pulse*0.24f),1);
}
inline void Draw(ImDrawList* draw, ImVec2 origin, ImVec2 size, float scale,
                 float radius, const State& state, bool reduced=false,
                 float header=0, float content=0) {
    if(header<=0)header=100*scale;
    if(content<=0)content=174*scale;
    const float strength = 0.35f+0.65f*state.reveal;
    const Lighting lights=Lights(size,state.time);
    draw->PushClipRect(origin, ImVec2(origin.x+size.x,origin.y+size.y),true);
    // Fixed tessellation, using the existing atlas white pixel; no blur passes,
    // textures, heap containers, or resource creation in this effect.
    draw->PrimReserve(Columns*Rows*6,(Columns+1)*(Rows+1));
    const unsigned base=draw->_VtxCurrentIdx;
    const ImVec2 uv=ImGui::GetFontTexUvWhitePixel();
    for (int y=0;y<=Rows;++y) {
        const ImVec2 edge=MeshPoint(0,y,size,radius);
        for(int x=0;x<=Columns;++x) {
            const ImVec2 p(edge.x+(size.x-2*edge.x)*x/Columns,edge.y);
            ImVec4 material=Material(p,size,lights,header,content);
            material.w*=strength;
            draw->PrimWriteVtx(ImVec2(origin.x+p.x,origin.y+p.y),uv,
                               ImGui::GetColorU32(material));
        }
    }
    for (int y=0;y<Rows;++y) for(int x=0;x<Columns;++x) {
        const unsigned a=base+y*(Columns+1)+x,b=a+1,c=a+Columns+1,d=c+1;
        for(unsigned index:{a,b,c,b,d,c})draw->PrimWriteIdx(static_cast<ImDrawIdx>(index));
    }
    for (int i=0;i<(reduced ? StationaryCount : ParticleCount);++i) {
        const auto& seed=particles[i];
        const bool ember=i>=StationaryCount && i<StationaryCount+EmberCount;
        const bool sparkle=i>=StationaryCount+EmberCount;
        const float pulse=sparkle ? Spark(seed,state.time) : 0;
        const ImVec2 p=ember ? Particle(seed,size,state.time) : ImVec2(seed.x*size.x,seed.y*size.y);
        const float r=std::max(0.55f,(seed.radius+(sparkle ? pulse*0.6f : 0))*scale);
        const float halo=r+(sparkle ? 3 : 2)*scale;
        if (!Contains(p,size,radius,halo+1)) continue;
        const ImVec2 center(origin.x+p.x,origin.y+p.y);
        const float alpha=(sparkle ? 0.20f+pulse*0.55f : ember ? 0.30f : 0.17f+seed.radius*0.12f)*strength;
        if(ember || sparkle)
            draw->AddCircleFilled(center,halo,ImGui::GetColorU32(Claude::Hex(0xFF5664,alpha*0.12f)),8);
        draw->AddCircleFilled(center,r,ImGui::GetColorU32(Claude::Hex(ember ? 0xD47B8C : 0xE2D5DA,alpha)),12);
        if(sparkle && pulse>0.05f) {
            KennyPaint::Seam(draw,ImVec2(center.x-halo,center.y),halo*2,
                Claude::Hex(0xF6F2F3,pulse*0.24f),0.7f);
        }
    }
    // Inward edge illumination leaves overlay pixels outside the shell alone.
    const float inset=std::max(2.0f,2*scale);
    draw->AddRect(ImVec2(origin.x+inset,origin.y+inset),
                  ImVec2(origin.x+size.x-inset,origin.y+size.y-inset),
                  ImGui::GetColorU32(Claude::Hex(0xC6ADB5,0.085f*strength)),
                  std::max(0.0f,radius-inset),0,1.0f);
    if(!reduced)Glint(draw,origin,size,scale,state.time);
    draw->PopClipRect();
}
} // namespace KennyEffects
