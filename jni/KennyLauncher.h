#pragma once
#include "KennyMenu.h"

namespace KennyLauncher {
struct Logo {
    KennyThemeBackground::ArtworkFrame image;
    // External asset owner uploads transparent RGBA and clears this reference
    // BEFORE releasing the texture/context. No final logo is invented here.
    void Set(KennyThemeBackground::ArtworkFrame frame){image=frame.Valid()?frame:KennyThemeBackground::ArtworkFrame{};}
    void Clear(){image={};}
    void Draw(ImDrawList* draw,ImVec2 center,float side) const {
        if(!image.Valid()) {KennyIdentity::Emblem(draw,center,side/48.0f);return;}
        KennyIdentity::Photo(draw,center,side,image.texture,image.width,image.height);
    }
};
struct State {
    bool target=false,dragged=false;
    float alpha=0;
    ImVec2 position{20,20};
    Logo logo;
    bool Request(bool next,const KennyAppearance::Preferences& p,KennyAudio::Dispatcher* audio,double time) {
        if(target==next)return false;
        target=next;
        if(p.reducedMotion)alpha=next?1.0f:0.0f;
        if(audio)audio->Emit(next ? KennyAudio::Event::MenuOpen:KennyAudio::Event::MenuClose,p,time);
        return true;
    }
    void Advance(float dt,bool reduced) {
        alpha=reduced ? (target?1.0f:0.0f) : KennyMotion::Step(alpha,target?1.0f:0.0f,24,dt);
        if(alpha<.005f)alpha=0;
        if(alpha>.995f)alpha=1;
    }
    bool DrawMenu()const{return target || alpha>0;}
};
inline float Side(ImVec2 viewport){return std::clamp(64*KennyMenu::Measure(viewport).scale,48.0f,80.0f);}
inline void Draw(State& state,const KennyAppearance::Preferences& p,KennyAudio::Dispatcher* audio,ImVec2 viewport) {
    if(state.DrawMenu() || viewport.x<=0 || viewport.y<=0)return;
    KennyMotion::ScopedReduction reduced(p.reducedMotion);
    const float side=std::min(Side(viewport),std::min(viewport.x,viewport.y));
    state.position=KennyMenu::Constrain(state.position,ImVec2(side,side),viewport);
    ImGui::SetNextWindowPos(state.position,ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(side,side),ImGuiCond_Always);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding,ImVec2(0,0));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize,0);
    ImGui::PushStyleColor(ImGuiCol_WindowBg,ImVec4(0,0,0,0));
    const auto flags=ImGuiWindowFlags_NoDecoration|ImGuiWindowFlags_NoSavedSettings|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoScrollbar;
    if(ImGui::Begin("##kenny-launcher",nullptr,flags)) {
        ImGui::SetCursorPos(ImVec2(0,0));
        const bool tapped=ImGui::InvisibleButton("Open KennyPvtHax",ImVec2(side,side));
        if(ImGui::IsItemActivated())state.dragged=false;
        if(ImGui::IsItemActive() && ImGui::IsMouseDragging(0)) {
            state.dragged=true;const auto delta=ImGui::GetIO().MouseDelta;
            state.position=KennyMenu::Constrain(ImVec2(state.position.x+delta.x,state.position.y+delta.y),ImVec2(side,side),viewport);
            ImGui::SetWindowPos(state.position);
        }
        if(tapped && !state.dragged)state.Request(true,p,audio,ImGui::GetTime());
        auto* draw=ImGui::GetWindowDrawList();const ImVec2 origin=ImGui::GetWindowPos();
        const ImVec2 center(origin.x+side*.5f,origin.y+side*.5f);
        const float emphasis=KennyMotion::Sample(ImGui::GetItemID(),5,ImGui::IsItemHovered()?1.0f:0.0f);
        const bool classic=p.theme==KennyAppearance::Theme::Classic;
        if(!state.logo.image.Valid())KennyPaint::Disc(draw,center,side*.48f,Claude::Hex(classic?0x191217:0x32131E),Claude::Hex(0x070609));
        if(!state.logo.image.Valid())draw->AddCircle(center,side*.48f,ImGui::GetColorU32(Claude::Hex(classic?0x88717B:0xE78695,.30f+emphasis*.22f)),40,1);
        state.logo.Draw(draw,center,side);
        ImGui::RenderNavHighlight(ImRect(origin,ImVec2(origin.x+side,origin.y+side)),ImGui::GetItemID());
    }
    ImGui::End();ImGui::PopStyleColor();ImGui::PopStyleVar(2);
}
} // namespace KennyLauncher
