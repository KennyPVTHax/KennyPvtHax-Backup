#pragma once
#include "KennyPanels.h"
#include "KennyThemePreferences.h"

// All controls are presentation-only; feature bindings stay in main.cpp.
namespace KennyAppearance {
inline void ThemeCard(Preferences& p, Theme theme, const char* description) {
    const float width=ImGui::GetContentRegionAvail().x;
    const float scale=KennyControls::Scale();
    const float height=std::max(96.0f,132.0f*scale);
    const ImVec2 start=ImGui::GetCursorScreenPos();
    for(ImGuiCol c:{ImGuiCol_Button,ImGuiCol_ButtonHovered,ImGuiCol_ButtonActive,ImGuiCol_Text})
        ImGui::PushStyleColor(c,ImVec4(0,0,0,0));
    if(ImGui::Button(ThemeName(theme),ImVec2(width,height))) p.theme=theme;
    ImGui::PopStyleColor(4);
    const float emphasis=KennyMotion::Sample(ImGui::GetItemID(),0,p.theme==theme ? 1.0f : 0.0f);
    const float hover=KennyMotion::Sample(ImGui::GetItemID(),1,ImGui::IsItemHovered() ? 1.0f : 0.0f);
    auto* draw=ImGui::GetWindowDrawList();
    draw->AddRectFilled(start,ImVec2(start.x+width,start.y+height),
        ImGui::GetColorU32(KennyMotion::Mix(Claude::Hex(0x191217,.78f),
                          Claude::Hex(0x470D19,.78f),emphasis*.65f+hover*.1f)),14*scale);
    draw->AddRect(start,ImVec2(start.x+width,start.y+height),
        ImGui::GetColorU32(KennyMotion::Mix(Claude::Hex(0x665059,.35f),
                          Claude::Hex(0xEA8796,.62f),emphasis)),14*scale);
    const float pad=std::max(10.0f,16*scale);
    // Quiet typographic cards: no substitute anime artwork or custom logo.
    draw->AddText(ImVec2(start.x+pad,start.y+pad),
                  ImGui::GetColorU32(p.theme==theme ? Claude::Hex(0xF4C8D0) : Claude::Dark::textPrimary),ThemeName(theme));
    const float textWidth=std::max(1.0f,width-2*pad);
    draw->AddText(ImGui::GetFont(),ImGui::GetFontSize()*.72f,
                  ImVec2(start.x+pad,start.y+pad+ImGui::GetFontSize()+10*scale),
                  ImGui::GetColorU32(Claude::Dark::textSecondary),description,nullptr,textWidth);
    KennyPaint::Seam(draw,ImVec2(start.x+pad,start.y+height-10*scale),width-2*pad,
                    Claude::Hex(0xEA8796,.12f+.45f*emphasis),1);
    ImGui::RenderNavHighlight(ImRect(start,ImVec2(start.x+width,start.y+height)),ImGui::GetItemID());
}
inline void DrawStyle(Preferences& p, bool artworkReady=false, const char* storageStatus=nullptr) {
    if(KennyPanels::Begin("##themes",3,4.0f)) {
        ImGui::TableNextColumn();ThemeCard(p,Theme::Aurora,"Living crimson light");
        ImGui::TableNextColumn();ThemeCard(p,Theme::Anime,"Your artwork, your atmosphere");
        ImGui::TableNextColumn();ThemeCard(p,Theme::Classic,"Quiet black and crimson");
        KennyPanels::End();
    }
    if(KennyPanels::Begin("##appearance",3,12.0f)) {
        KennyPanels::Section("Surface");
        KennyControls::SliderFloat("Menu opacity",&p.opacity,85.0f,100.0f,"%.0f%%");
        KennyPanels::Note("Text and controls keep their contrast.");KennyPanels::EndSection();
        KennyPanels::Section("Layout");
        KennyControls::Choice("Row spacing",&p.compactRows,"Standard","Compact");
        KennyPanels::Note("Applied immediately to every panel.");KennyPanels::EndSection();
        KennyPanels::Section("Motion");
        KennyControls::Choice("Atmosphere",&p.reducedMotion,"Full","Reduced");
        KennyPanels::Note("Reduced holds the background and makes transitions immediate.");KennyPanels::EndSection();
        KennyPanels::End();
    }
    if(p.theme==Theme::Aurora && KennyPanels::Begin("##aurora-settings",2,12.0f,"Touch attraction")) {
        KennyPanels::Section("Aurora light");
        KennyControls::SliderFloat("Aurora intensity",&p.auroraIntensity,0,100,"%.0f%%");
        KennyControls::SliderFloat("Particle activity",&p.particleActivity,0,100,"%.0f%%");
        KennyPanels::Note("Zero activity holds stars in place; the curtains keep flowing.");KennyPanels::EndSection();
        KennyPanels::Section("Starfield interaction");
        KennyControls::Checkbox("Show stars",&p.starsVisible);
        KennyControls::Checkbox("Touch attraction",&p.touchAttraction);
        KennyPanels::Note("Only empty content reacts. Controls and the drag header keep priority.");KennyPanels::EndSection();
        KennyPanels::End();
    } else if(p.theme==Theme::Anime) {
        if(artworkReady && KennyPanels::Begin("##artwork",2,12.0f)) {
            KennyPanels::Section("Artwork surface");
            KennyControls::SliderFloat("Artwork dimming",&p.artworkDim,35,95,"%.0f%%");KennyPanels::EndSection();
            KennyPanels::Section("Composition");
            KennyControls::Choice("Artwork fit",&p.artworkCover,"Contain","Cover");KennyPanels::EndSection();
            KennyPanels::End();
        } else KennyPanels::Note("Anime is selected. No artwork is installed yet; a quiet dark surface keeps every control usable. Your artwork will appear here when installed.");
    } else if(p.theme==Theme::Classic) {
        KennyPanels::Note("Classic uses static black and crimson surfaces. Animated backgrounds stay off.");
    }
    Normalize(p);
    if(storageStatus) KennyPanels::Note(storageStatus);
}

inline void DrawSettings(Preferences& preferences, bool& centerRequested) {
    if (!KennyPanels::Begin("##general", 2, 12.0f)) return;
    KennyPanels::Section("Menu");
    if (KennyControls::Button("Center window")) centerRequested = true;
    if (KennyControls::Button("Reset appearance")) preferences = Preferences{};
    KennyPanels::Note("Restore Aurora and all default appearance preferences.");
    KennyPanels::EndSection();
    KennyPanels::Section("About");
    ImGui::TextUnformatted("KennyPvtHax");
    KennyPanels::Note("Crimson Eclipse");
    KennyPanels::Note("Android landscape interface");
    KennyPanels::EndSection();
    KennyPanels::End();
}

} // namespace KennyAppearance
