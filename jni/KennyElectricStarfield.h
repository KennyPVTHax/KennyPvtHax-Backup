#pragma once
#include <array>
#include "KennyThemeBackground.h"

// Presentation only. Analytic, temporally coherent geometry; no textures,
// threads, random per-frame topology, input ownership or audio dependency.
namespace KennyElectric {
constexpr int StarCapacity=96, Filaments=17, Segments=32, MaxPulses=2;
struct Star { float x,y,radius,light,phase; };
constexpr std::array<Star,StarCapacity> Seeds() {
    std::array<Star,StarCapacity> result{};
    for(int i=0;i<StarCapacity;++i)result[i]={.025f+.95f*KennyEffects::Unit(i*7+401),
        .20f+.77f*KennyEffects::Unit(i*7+402),.65f+.75f*KennyEffects::Unit(i*7+403),
        .20f+.38f*KennyEffects::Unit(i*7+404),6.2831853f*KennyEffects::Unit(i*7+405)};
    return result;
}
inline constexpr auto stars=Seeds();
struct State {
    double time=0;
    int frame=-2;
    std::array<std::array<ImVec2,Segments+1>,Filaments> paths{};
    unsigned updates=0;
    void Advance(int next,float dt,const KennyAppearance::Preferences& p) {
        if(frame==next)return;
        const bool gap=frame!=next-1;frame=next;
        if(gap||!p.electricStarfield||p.reducedMotion||p.electricReducedMotion)return;
        const float speed=KennyAppearance::Bounded(p.electricSpeed,0,100,50)*.02f;
        time+=KennyMotion::Delta(dt)*speed;
        if(speed>0)++updates;
    }
};
inline ImVec2 Add(ImVec2 a,ImVec2 b){return ImVec2(a.x+b.x,a.y+b.y);}
inline ImVec2 Mul(ImVec2 a,float b){return ImVec2(a.x*b,a.y*b);}
inline ImVec2 Mix(ImVec2 a,ImVec2 b,float t){return Add(Mul(a,1-t),Mul(b,t));}
// Clamp the complete halo and line fringe into the convex rounded interior.
inline ImVec2 Safe(ImVec2 p,ImVec2 size,float radius,float margin) {
    ImVec2 inner(std::max(1.0f,size.x-2*margin),std::max(1.0f,size.y-2*margin));
    return Add(ImVec2(margin,margin),KennyAurora::Inside(ImVec2(p.x-margin,p.y-margin),inner,std::max(0.0f,radius-margin)));
}
inline float Noise(double x,unsigned seed){return KennyAurora::Noise(x,seed)*2-1;}
inline ImVec2 Node(int i,ImVec2 size,double time) {
    // Connected perimeter network. No lattice/dashboard is copied from video.
    constexpr float xy[9][2]={{.028f,.27f},{.042f,.66f},{.18f,.89f},{.43f,.93f},
        {.70f,.92f},{.88f,.86f},{.969f,.61f},{.967f,.27f},{.55f,.79f}};
    return ImVec2(size.x*(xy[i][0]+.008f*Noise(time*.075+i*1.71,91)),
                  size.y*(xy[i][1]+.010f*Noise(time*.063+i*1.11,113)));
}
inline ImVec2 Curve(ImVec2 a,ImVec2 b,int id,float u,double time,float scale) {
    const ImVec2 d(b.x-a.x,b.y-a.y);const float len=std::max(1.0f,std::hypot(d.x,d.y));
    const ImVec2 normal(-d.y/len,d.x/len);
    const float envelope=4*u*(1-u);
    // Broad bend plus two smooth noise octaves: coherent thin branching strands.
    const float bend=(id%2 ? -1.0f : 1.0f)*(.055f*len)+
        scale*(6*Noise(u*2.7+time*.17,id*17+31)+2.5f*Noise(u*10.1-time*.24,id*19+79));
    return Add(Mix(a,b,u),Mul(normal,envelope*bend));
}
inline void Prepare(State& state,ImVec2 size,float radius,float scale) {
    constexpr int ends[10][2]={{0,1},{1,2},{2,3},{3,4},{4,5},{5,6},{6,7},{2,8},{8,5},{3,8}};
    for(int j=0;j<Filaments;++j) {
        ImVec2 a{},b{};
        if(j<10){a=Node(ends[j][0],size,state.time);b=Node(ends[j][1],size,state.time);}
        else if(j<14) {const int parent=(j-10)*2; a=state.paths[parent][Segments/2];
            b=Add(a,ImVec2((j%2 ? -1.f : 1.f)*size.x*.065f,-size.y*.075f));}
        if(j>=14){const int parent=(j-14)*3;
            for(int k=0;k<=Segments;++k){const auto v=state.paths[parent][k];const auto prev=state.paths[parent][std::max(0,k-1)],next=state.paths[parent][std::min(Segments,k+1)];
                const float dx=next.x-prev.x,dy=next.y-prev.y,len=std::max(1.f,std::hypot(dx,dy)),u=float(k)/Segments;
                const float braid=4*u*(1-u)*scale*(4+5*Noise(u*3.8+state.time*.12,j*37+41));
                state.paths[j][k]=Safe(Add(v,ImVec2(-dy/len*braid,dx/len*braid)),size,radius,10*scale+1);
            }
        }else for(int k=0;k<=Segments;++k)state.paths[j][k]=Safe(Curve(a,b,j,float(k)/Segments,state.time,scale),size,radius,10*scale+1);
    }
}
inline float Quiet(ImVec2 p,ImVec2 size,float content,float scale) {
    const float edge=std::clamp(std::abs(p.x/size.x-.5f)*2,0.0f,1.0f);
    const float lower=std::clamp((p.y-content-230*scale)/std::max(1.f,size.y-content-230*scale),0.f,1.f);
    return .23f+.77f*std::max(edge*edge,lower);
}
inline void Strip(ImDrawList* draw,const std::array<ImVec2,Segments+1>& points,
                  ImVec2 origin,ImVec2 size,float content,float scale,float width,unsigned color,
                  float alpha,double time,int id,bool moving,float progress=-1,float energy=0) {
    const auto uv=ImGui::GetFontTexUvWhitePixel();const unsigned base=draw->_VtxCurrentIdx;
    draw->PrimReserve(Segments*6,(Segments+1)*2);
    for(int k=0;k<=Segments;++k){const auto& p=points[k];const auto& prev=points[std::max(0,k-1)];const auto& next=points[std::min(Segments,k+1)];
        const float dx=next.x-prev.x,dy=next.y-prev.y,len=std::max(1.f,std::hypot(dx,dy));
        const float u=float(k)/Segments;
        const float flicker=moving ? .82f+.18f*KennyAurora::Noise(time*.48+u*3.7,id*53+181) : .85f;
        const float tail=(u-progress)/.075f;
        const float strength=std::min(.9f,(alpha*flicker*(.55f+.45f*std::sin(u*3.14159265f))+energy*std::exp(-tail*tail))*Quiet(p,size,content,scale));
        const auto c=ImGui::GetColorU32(Claude::Hex(color,strength));
        const ImVec2 n(-dy/len*width*.5f,dx/len*width*.5f);
        draw->PrimWriteVtx(Add(origin,Add(p,n)),uv,c);draw->PrimWriteVtx(Add(origin,Add(p,Mul(n,-1))),uv,c);
    }
    for(int k=0;k<Segments;++k){const unsigned a=base+k*2;for(unsigned n:{a,a+1,a+2,a+1,a+3,a+2})draw->PrimWriteIdx(static_cast<ImDrawIdx>(n));}
}
inline ImVec2 Along(const std::array<ImVec2,Segments+1>& path,float u) {
    const float value=std::clamp(u,0.f,1.f)*Segments;const int k=std::min(Segments-1,int(value));
    return Mix(path[k],path[k+1],value-k);
}
struct Pulse {int path=0;float progress=0,alpha=0;};
inline Pulse Energy(double time,int slot) {
    const double period=slot ? 9.7 : 8.3;
    const double cycle=std::floor((time+slot*4.1)/period);
    const double age=time+slot*4.1-cycle*period;
    const float progress=static_cast<float>((age-1.0)/2.2);
    if(progress<=0||progress>=1)return {};
    const int path=int(KennyEffects::Hash(static_cast<unsigned>(static_cast<unsigned long long>(cycle))+slot*29+701)%10);
    return {path,progress,std::sin(progress*3.14159265f)};
}
inline void Dot(ImDrawList* draw,ImVec2 origin,ImVec2 p,float radius,float scale,float alpha,unsigned color,bool halo) {
    const ImVec2 at=Add(origin,p);
    if(halo){draw->AddCircleFilled(at,radius+3*scale,ImGui::GetColorU32(Claude::Hex(0xFF3656,alpha*.085f)),10);
        draw->AddCircleFilled(at,radius+1.4f*scale,ImGui::GetColorU32(Claude::Hex(color,alpha*.14f)),10);}
    draw->AddCircleFilled(at,radius,ImGui::GetColorU32(Claude::Hex(color,alpha)),8);
}
inline void Draw(ImDrawList* draw,ImVec2 origin,ImVec2 size,float scale,float radius,State& state,
                 const KennyAppearance::Preferences& p,float header,float content) {
    if(!p.electricStarfield||size.x<1||size.y<1)return;
    const bool moving=!(p.reducedMotion||p.electricReducedMotion||p.electricSpeed<=0);
    const float lightning=KennyAppearance::Bounded(p.electricLightning,0,100,45)*.01f;
    const float sparkle=KennyAppearance::Bounded(p.electricSparkle,0,100,55)*.01f;
    draw->PushClipRect(origin,Add(origin,size),true);
    // One reusable atlas mesh for faint energy illumination, darker over text.
    const auto uv=ImGui::GetFontTexUvWhitePixel();const unsigned base=draw->_VtxCurrentIdx;
    draw->PrimReserve(KennyEffects::Columns*KennyEffects::Rows*6,(KennyEffects::Columns+1)*(KennyEffects::Rows+1));
    for(int y=0;y<=KennyEffects::Rows;++y)for(int x=0;x<=KennyEffects::Columns;++x){const auto v=KennyEffects::MeshPoint(x,y,size,radius);
        const float light=KennyEffects::Bloom(v,Node(2,size,state.time),size.x*.40f,size.y*.56f)+.7f*KennyEffects::Bloom(v,Node(6,size,state.time),size.x*.32f,size.y*.58f);
        const float shelf=v.y<header ? .25f : 1.f;
        const ImVec4 color=KennyMotion::Mix(Claude::Hex(0x08070A,.30f),Claude::Hex(0x64152A,.42f),std::min(.65f,light*.45f*lightning*shelf));
        draw->PrimWriteVtx(Add(origin,v),uv,ImGui::GetColorU32(color));}
    KennyAurora::GridIndices(draw,base,KennyEffects::Columns,KennyEffects::Rows);
    std::array<Pulse,MaxPulses> pulses{};
    if(moving&&p.electricPulses)for(int i=0;i<MaxPulses;++i)pulses[i]=Energy(state.time,i);
    if(lightning>0){Prepare(state,size,radius,scale);
        // Layered, tapered ribbons. No line/glow extends beyond rounded bounds.
        for(int layer=0;layer<3;++layer)for(int j=0;j<Filaments;++j){
            const float variation=.50f+.50f*KennyEffects::Unit(j*23+989);
            const float widths[]={9.f,1.6f,.80f};const float alphas[]={.16f,.74f,.85f};const unsigned colors[]={0xC41632,0xFF3656,0xF5F3FF};
            Pulse local{};for(const auto& pulse:pulses)if(pulse.alpha>local.alpha&&pulse.path==j)local=pulse;
            Strip(draw,state.paths[j],origin,size,content,scale,widths[layer]*scale,colors[layer],alphas[layer]*(layer==2 ? std::sqrt(lightning) : lightning)*variation,state.time,j,moving,local.progress,local.alpha*std::sqrt(lightning)*(layer==2?.60f:layer==1?.35f:.16f));}
        for(int i=0;i<9;++i){const auto at=Safe(Node(i,size,state.time),size,radius,7*scale+1);
            Dot(draw,origin,at,1.25f*scale,scale,.80f*std::sqrt(lightning)*Quiet(at,size,content,scale),0xF5F3FF,true);}
    }
    const int count=32*(std::clamp(p.electricDensity,0,2)+1);
    for(int i=0;i<count&&sparkle>0;++i){const auto& s=stars[i];const bool drift=i%4==1,glint=i%13==0;
        // Reduced freezes the current pose and luminosity rather than resetting.
        auto at=ImVec2((s.x+(drift ? .009f*Noise(state.time*.12+s.phase,601) : 0))*size.x,
                       (s.y+(drift ? .012f*Noise(state.time*.10+s.phase,619) : 0))*size.y);
        at=Safe(at,size,radius,8*scale+1);
        const float twinkle=.68f+.32f*static_cast<float>(std::sin(state.time*.7+s.phase)*.5+.5);
        const float flash=glint ? std::pow(KennyAurora::Noise(state.time*.18+s.phase,647),12.f) : 0;
        const float alpha=(s.light*twinkle+flash*.30f)*sparkle*1.35f*Quiet(at,size,content,scale);
        Dot(draw,origin,at,std::max(.35f,s.radius*scale),scale,alpha,drift?0xFF3656:0xF5F3FF,glint||drift);
        if(glint&&flash>.12f){const auto c=ImGui::GetColorU32(Claude::Hex(0xF5F3FF,alpha*flash*.55f));const auto q=Add(origin,at);
            draw->AddLine(Add(q,ImVec2(-3*scale,0)),Add(q,ImVec2(3*scale,0)),c,.6f*scale);
            draw->AddLine(Add(q,ImVec2(0,-3*scale)),Add(q,ImVec2(0,3*scale)),c,.6f*scale);}
    }
    if(moving&&p.electricPulses&&lightning>0)for(int i=0;i<MaxPulses;++i){const auto pulse=pulses[i];if(pulse.alpha<=0)continue;
        for(int tail=5;tail>=0;--tail){const float u=pulse.progress-tail*.013f;if(u<0)continue;const auto at=Along(state.paths[pulse.path],u);
            const float alpha=pulse.alpha*std::sqrt(lightning)*(tail ? .20f*(1-tail/6.f) : .9f)*Quiet(at,size,content,scale);
            Dot(draw,origin,at,(tail ? .8f : 1.9f)*scale,scale,alpha,0xF5F3FF,tail==0);}
    }
    draw->PopClipRect();
}
} // namespace KennyElectric
