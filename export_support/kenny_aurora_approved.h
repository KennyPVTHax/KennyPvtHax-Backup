#pragma once
#include <array>
#include <cmath>
#include "KennyEffects.h"

// Phase A: presentation-only, bounded state. Native ImGui retains input ownership.
namespace KennyAuroraApproved {
constexpr int StarCount = 40, Layers = 3, Columns = 96, Rows = 18;
constexpr float FixedStep = 1.0f / 120.0f;
inline float Smooth(float v) { v = std::clamp(v, 0.0f, 1.0f); return v*v*(3-2*v); }
inline float Noise(double x, unsigned seed) {
    const double cell = std::floor(x);
    const unsigned key = static_cast<unsigned>(static_cast<long long>(cell));
    const float f = Smooth(static_cast<float>(x-cell));
    const float a = KennyEffects::Unit(key ^ seed);
    return a + (KennyEffects::Unit((key+1) ^ seed)-a)*f;
}
inline float Field(double x, double t, unsigned seed) {
    return .57f*Noise(x+t,seed) + .28f*Noise(x*2.17-t*.73,seed+71)
         + .15f*Noise(x*4.31+t*.37,seed+131);
}
struct Star { ImVec2 position, velocity; float radius = 0, luminosity = 0; };
struct State {
    std::array<Star,StarCount> stars{};
    double time = 0;
    float accumulator = 0, response = 0;
    ImVec2 touch{.5f,.75f};
    bool initialized = false, gesture = false;
    int frame = -2;

    static ImVec2 Home(int i, double time) {
        // Seeded jitter, no uniform grid, wrap or respawn discontinuities.
        const float x = .09f + .82f*KennyEffects::Unit(i*11+319);
        const float y = .09f + .82f*KennyEffects::Unit(i*11+761);
        const float speed = .028f + .018f*KennyEffects::Unit(i*11+503);
        return ImVec2(x + .025f*(Field(i*1.73,time*speed,47)-.5f),
                      y + .035f*(Field(i*2.11,time*speed,211)-.5f));
    }
    void Initialize() {
        if(initialized) return;
        for(int i=0;i<StarCount;++i)
            stars[i] = {Home(i,time),ImVec2(0,0), .55f+KennyEffects::Unit(i*11+887)*.85f,
                         .25f+KennyEffects::Unit(i*11+997)*.48f};
        initialized = true;
    }
    void Step(float dt, ImVec2 size, bool down) {
        time += dt;
        response = KennyMotion::Step(response,down ? 1.0f : 0.0f,down ? 7.0f : 2.8f,dt);
        const float aspect = size.x / std::max(1.0f,size.y);
        const float damping = std::exp(-4.8f*dt);
        for(int i=0;i<StarCount;++i) {
            auto& star = stars[i];
            const ImVec2 home = Home(i,time);
            const float dx = (touch.x-star.position.x)*aspect, dy = touch.y-star.position.y;
            const float distance = std::sqrt(dx*dx+dy*dy);
            const float weight = down ? Smooth(1-distance/.38f)*response : 0;
            // Home spring always survives attraction: stars retain a spread,
            // release disperses continuously instead of respawning them.
            const float ax = (home.x-star.position.x)*3.5f + (touch.x-star.position.x)*22*weight;
            const float ay = (home.y-star.position.y)*3.5f + (touch.y-star.position.y)*22*weight;
            star.velocity.x = (star.velocity.x+ax*dt)*damping;
            star.velocity.y = (star.velocity.y+ay*dt)*damping;
            const float speed = std::hypot(star.velocity.x*aspect,star.velocity.y);
            if(speed>.28f) { star.velocity.x*=.28f/speed; star.velocity.y*=.28f/speed; }
            star.position.x += star.velocity.x*dt;
            star.position.y += star.velocity.y*dt;
            // Conservative interior bounds, independent of canvas resolution.
            for(int axis=0;axis<2;++axis) {
                float& p = axis ? star.position.y : star.position.x;
                float& v = axis ? star.velocity.y : star.velocity.x;
                if(p<.065f) { p=.065f; v=std::max(0.0f,v); }
                if(p>.935f) { p=.935f; v=std::min(0.0f,v); }
            }
        }
    }
    void Advance(int nextFrame, float dt, ImVec2 size, bool down, ImVec2 target, bool reduced) {
        Initialize();
        if(nextFrame==frame) return;
        const bool resumed = nextFrame!=frame+1;
        frame = nextFrame;
        if(resumed || reduced) {
            accumulator = 0; response = 0; gesture = down && !reduced;
            return; // No hidden time catch-up or reduced-motion physics.
        }
        if(!std::isfinite(target.x) || !std::isfinite(target.y)) down=false;
        const float elapsed = KennyMotion::Delta(dt);
        if(down) {
            // Position input is visual-only; no writes to IO or feature values.
            touch.x=KennyMotion::Step(touch.x,std::clamp(target.x,0.0f,1.0f),14,elapsed);
            touch.y=KennyMotion::Step(touch.y,std::clamp(target.y,0.0f,1.0f),14,elapsed);
        }
        accumulator += elapsed;
        // At most twelve 120 Hz steps, even after a stall. Remainder is retained.
        for(int step=0;step<12 && accumulator+1e-7f>=FixedStep;++step) {
            Step(FixedStep,size,down);
            accumulator=std::max(0.0f,accumulator-FixedStep);
        }
    }
};

// Project onto an inset convex rounded shell. All triangles are inside it,
// including ribbons reaching a rounded corner; rectangular scissoring alone
// would leave bright corner artifacts.
inline ImVec2 Inside(ImVec2 p, ImVec2 size, float radius) {
    const float inset=.8f, r=std::max(0.0f,std::min(radius-inset,std::min(size.x,size.y)*.5f-inset));
    p.x=std::clamp(p.x,inset,size.x-inset); p.y=std::clamp(p.y,inset,size.y-inset);
    const ImVec2 center(std::clamp(p.x,inset+r,size.x-inset-r),
                        std::clamp(p.y,inset+r,size.y-inset-r));
    const float dx=p.x-center.x, dy=p.y-center.y, length=std::hypot(dx,dy);
    if(length>r && length>0) { p.x=center.x+dx*r/length; p.y=center.y+dy*r/length; }
    return p;
}
inline void GridIndices(ImDrawList* draw, unsigned base, int columns, int rows) {
    for(int y=0;y<rows;++y) for(int x=0;x<columns;++x) {
        const unsigned a=base+y*(columns+1)+x,b=a+1,c=a+columns+1,d=c+1;
        for(unsigned i:{a,b,c,b,d,c}) draw->PrimWriteIdx(static_cast<ImDrawIdx>(i));
    }
}
struct CurtainColumn { float lower, height, fold, light, lean; };
inline CurtainColumn Curtain(float x, double time, int layer) {
    const unsigned seed=137+layer*313;
    const double drift=time*(.105+layer*.031);
    // Advected multiscale noise creates unequal folds, wandering lower hems
    // and fine vertical rays. No repeating sine strip or radial bloom.
    const float sweep=Field(x*4.6,drift,seed);
    const float fold=Field(x*14.3,drift*1.31,seed+9);
    const float ray=Noise(x*47.7-drift*.57,seed+37);
    return { .67f+layer*.10f+(sweep-.5f)*.28f+(fold-.5f)*.035f,
             .27f+Field(x*5.1,drift*.64,seed+29)*.31f,
             fold, .16f+.28f*fold+.56f*ray*ray,
             (Field(x*3.7,drift*.43,seed+63)-.5f)*.115f };
}
inline void Draw(ImDrawList* draw, ImVec2 origin, ImVec2 size, float scale, float radius,
                 const State& state, bool reduced, float header, float content) {
    draw->PushClipRect(origin,ImVec2(origin.x+size.x,origin.y+size.y),true);
    const ImVec2 uv=ImGui::GetFontTexUvWhitePixel();
    // Quiet graphite/burgundy surface hierarchy, without the previous blooms.
    draw->PrimReserve(KennyEffects::Columns*KennyEffects::Rows*6,
                      (KennyEffects::Columns+1)*(KennyEffects::Rows+1));
    unsigned base=draw->_VtxCurrentIdx;
    for(int y=0;y<=KennyEffects::Rows;++y) for(int x=0;x<=KennyEffects::Columns;++x) {
        const ImVec2 p=KennyEffects::MeshPoint(x,y,size,radius);
        ImVec4 c=Claude::Hex(0x120A10,.32f);
        if(p.y<header) c=Claude::Hex(0x20171E,.27f);
        else if(p.y<content) c=Claude::Hex(0x100B0F,.35f);
        draw->PrimWriteVtx(ImVec2(origin.x+p.x,origin.y+p.y),uv,ImGui::GetColorU32(c));
    }
    GridIndices(draw,base,KennyEffects::Columns,KennyEffects::Rows);
    for(int layer=0;layer<Layers;++layer) {
        std::array<CurtainColumn,Columns+1> columns{};
        for(int x=0;x<=Columns;++x) {
            const float u=float(x)/Columns;
            columns[x]=Curtain(u,state.time,layer);
            columns[x].light*=.78f+.22f*Field(u*5,state.time*.08,layer+939);
        }
        draw->PrimReserve(Columns*Rows*6,(Columns+1)*(Rows+1));
        base=draw->_VtxCurrentIdx;
        for(int y=0;y<=Rows;++y) {
            const float v=float(y)/Rows;
            const float fade=Smooth(v/.33f)*Smooth((1-v)/.13f);
            const float hem=std::exp(-std::pow((v-.86f)/.115f,2.0f));
            for(int x=0;x<=Columns;++x) {
                const float u=float(x)/Columns;
                const auto& column=columns[x];
                float px=u + column.lean*(1-v)*(1-v);
                float py=column.lower-column.height*(1-v);
                const float dx=(px-state.touch.x)*(size.x/size.y), dy=py-state.touch.y;
                const float local=Smooth(1-std::hypot(dx,dy)/.31f)*state.response;
                px+=local*dx*.025f; py-=local*.022f*(1-v);
                const ImVec2 p=Inside(ImVec2(px*size.x,py*size.y),size,radius);
                const float composition=layer==1 ? .45f+.55f*Smooth(u/.40f) :
                    .30f+.70f*Smooth((.83f-u)/.45f);
                const float edges=Smooth(u/.13f)*Smooth((1-u)/.14f)*composition;
                const float shelf=Smooth((p.y-header*.65f)/(content+80*scale));
                const float light=column.light;
                ImVec4 c=KennyMotion::Mix(Claude::Hex(layer==0 ? 0x75142C : layer==1 ? 0xB01938 : 0xD12B43),
                                         Claude::Hex(0xF35B73),hem*.34f+local*.10f);
                c.w=fade*edges*shelf*light*(.24f+.25f*hem)*(1+local*.45f);
                draw->PrimWriteVtx(ImVec2(origin.x+p.x,origin.y+p.y),uv,ImGui::GetColorU32(c));
            }
        }
        GridIndices(draw,base,Columns,Rows);
    }
    for(int i=0;i<StarCount;++i) {
        const auto& star=state.stars[i];
        const ImVec2 p(star.position.x*size.x,star.position.y*size.y);
        const float twinkle=reduced ? .7f : .57f+.43f*Field(i*3.3,state.time*.55,i+1071);
        const float shimmer=(!reduced && i%13==0) ? std::pow(Noise(state.time*.28,i+1871),12.0f) : 0;
        const float r=std::max(.55f,star.radius*scale), halo=r+2.5f*scale;
        if(!KennyEffects::Contains(p,size,radius,halo+1)) continue;
        const float near=Smooth(1-std::hypot((star.position.x-state.touch.x)*size.x/size.y,
                                            star.position.y-state.touch.y)/.38f)*state.response;
        const float alpha=std::min(.95f,star.luminosity*twinkle+shimmer*.35f+near*.20f);
        const ImVec2 center(origin.x+p.x,origin.y+p.y);
        draw->AddCircleFilled(center,halo,ImGui::GetColorU32(Claude::Hex(0xFF5664,alpha*.085f)),8);
        draw->AddCircleFilled(center,r,ImGui::GetColorU32(Claude::Hex(i%4 ? 0xE3BCC7 : 0xF6EAF0,alpha)),12);
        if(shimmer>.10f) KennyPaint::Seam(draw,ImVec2(center.x-halo,center.y),halo*2,
                                          Claude::Hex(0xFFE6ED,shimmer*.25f),.7f);
    }
    draw->AddRect(ImVec2(origin.x+2*scale,origin.y+2*scale),
                  ImVec2(origin.x+size.x-2*scale,origin.y+size.y-2*scale),
                  ImGui::GetColorU32(Claude::Hex(0xC6ADB5,.085f)),radius-2*scale,0,1);
    draw->PopClipRect();
}
} // namespace KennyAurora
