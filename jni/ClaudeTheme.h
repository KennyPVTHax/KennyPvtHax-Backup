#pragma once
#include "imgui/imgui.h"
#include "KennyMotion.h"
namespace Claude {

// ---- Hex helper ------------------------------------------------------------
inline ImVec4 Hex(unsigned int h, float a = 1.0f) {
    return ImVec4(((h >> 16) & 0xFF) / 255.0f,
                  ((h >> 8)  & 0xFF) / 255.0f,
                  ( h        & 0xFF) / 255.0f, a);
}


// ---- KennyPvtHax black/crimson tokens -------------------------------------
namespace Dark {
    inline const ImVec4 bg            = Hex(0x08070A, 0.97f);
    inline const ImVec4 surface       = Hex(0x141014, 0.72f);
    inline const ImVec4 surfaceElev   = Hex(0x1A1012);
    inline const ImVec4 surfaceSubtle = Hex(0x26171B);
    inline const ImVec4 outline       = Hex(0x7A1C24, 0.55f);
    inline const ImVec4 textPrimary   = Hex(0xF5F2F2);
    inline const ImVec4 textSecondary = Hex(0xB7A9AC);
    inline const ImVec4 textTertiary  = Hex(0x867579);
    inline const ImVec4 accent        = Hex(0xC1121F);
    inline const ImVec4 glow          = Hex(0xFF5A5F);
    inline const ImVec4 accentPressed = Hex(0xE63946);
    inline const ImVec4 onAccent      = Hex(0x08070A);
    inline const ImVec4 accentSubtle  = Hex(0x34151C, 0.85f);
    inline const ImVec4 error         = Hex(0xE5776A);
    inline const ImVec4 success       = Hex(0x86B096);
    inline const ImVec4 warning       = Hex(0xD2A24C);
}

// ---- Layout constants ------------------------------------------------------
constexpr float Pad          = 16.0f;
constexpr float RowGap       = 8.0f;
constexpr float SectionGap   = 24.0f;
constexpr float NavRowHeight = 40.0f;
constexpr float RadiusBtn    = 10.0f;
constexpr float RadiusInput  = 8.0f;
constexpr float RadiusCard   = 12.0f;
constexpr float RadiusWindow = 34.0f;

// ---- Apply theme (call once after ImGui::CreateContext) --------------------
inline void Apply() {
    ImGuiStyle& s = ImGui::GetStyle();
    ImVec4* c = s.Colors;

    // Shape
    s.WindowRounding      = RadiusWindow;
    s.ChildRounding       = RadiusCard;
    s.FrameRounding       = RadiusInput;
    s.PopupRounding       = RadiusCard;
    s.GrabRounding        = RadiusInput;
    s.ScrollbarRounding   = RadiusInput;
    s.TabRounding         = RadiusInput;

    // Spacing
    s.WindowPadding       = ImVec2(Pad, Pad);
    s.FramePadding        = ImVec2(12, 7);
    s.ItemSpacing         = ImVec2(RowGap, RowGap);
    s.ItemInnerSpacing    = ImVec2(6, 6);
    s.ScrollbarSize       = 8.0f;
    s.GrabMinSize         = 12.0f;
    s.WindowBorderSize    = 1.0f;
    s.ChildBorderSize     = 1.0f;
    s.FrameBorderSize     = 0.0f;
    s.WindowTitleAlign    = ImVec2(0.0f, 0.5f);

    // Surfaces
    c[ImGuiCol_Text]                 = Dark::textPrimary;
    c[ImGuiCol_TextDisabled]         = Dark::textTertiary;
    c[ImGuiCol_WindowBg]             = Dark::bg;
    c[ImGuiCol_ChildBg]              = ImVec4(0, 0, 0, 0);
    c[ImGuiCol_PopupBg]              = Dark::surfaceElev;
    c[ImGuiCol_Border]               = Dark::outline;
    c[ImGuiCol_BorderShadow]         = ImVec4(0, 0, 0, 0);

    // Inputs
    c[ImGuiCol_FrameBg]              = Dark::surfaceSubtle;
    c[ImGuiCol_FrameBgHovered]       = Hex(0x32191F);
    c[ImGuiCol_FrameBgActive]        = Hex(0x442029);

    // Title / menu bar
    c[ImGuiCol_TitleBg]              = Dark::surfaceElev;
    c[ImGuiCol_TitleBgActive]        = Dark::surfaceElev;
    c[ImGuiCol_TitleBgCollapsed]     = Dark::surfaceElev;
    c[ImGuiCol_MenuBarBg]            = Dark::surface;

    // Scrollbar
    c[ImGuiCol_ScrollbarBg]          = ImVec4(0, 0, 0, 0);
    c[ImGuiCol_ScrollbarGrab]        = Dark::outline;
    c[ImGuiCol_ScrollbarGrabHovered] = Hex(0xA94752);
    c[ImGuiCol_ScrollbarGrabActive]  = Dark::accent;

    // Buttons — neutral by default (NOT accent)
    c[ImGuiCol_Button]               = ImVec4(0, 0, 0, 0);
    c[ImGuiCol_ButtonHovered]        = Dark::surfaceSubtle;
    c[ImGuiCol_ButtonActive]         = Hex(0x442029);

    // Accent-driven controls
    c[ImGuiCol_CheckMark]            = Dark::accent;
    c[ImGuiCol_SliderGrab]           = Dark::accent;
    c[ImGuiCol_SliderGrabActive]     = Dark::accentPressed;
    c[ImGuiCol_Header]               = Dark::accentSubtle;
    c[ImGuiCol_HeaderHovered]        = Hex(0x52212B);
    c[ImGuiCol_HeaderActive]         = Dark::accentSubtle;

    // Legacy tab enum names match the bundled ImGui version.
    c[ImGuiCol_Tab]                  = ImVec4(0, 0, 0, 0);
    c[ImGuiCol_TabHovered]           = Dark::surfaceSubtle;
    c[ImGuiCol_TabActive]            = Dark::accentSubtle;
    c[ImGuiCol_TabUnfocused]         = ImVec4(0, 0, 0, 0);
    c[ImGuiCol_TabUnfocusedActive]   = Dark::accentSubtle;

    // Separators
    c[ImGuiCol_Separator]            = Dark::outline;
    c[ImGuiCol_SeparatorHovered]     = Dark::accent;
    c[ImGuiCol_SeparatorActive]      = Dark::accentPressed;

    // Resize grips
    c[ImGuiCol_ResizeGrip]           = ImVec4(0, 0, 0, 0);
    c[ImGuiCol_ResizeGripHovered]    = Dark::accentSubtle;
    c[ImGuiCol_ResizeGripActive]     = Dark::accent;

    // Plots
    c[ImGuiCol_PlotLines]            = Dark::accent;
    c[ImGuiCol_PlotLinesHovered]     = Dark::accentPressed;
    c[ImGuiCol_PlotHistogram]        = Dark::accent;
    c[ImGuiCol_PlotHistogramHovered] = Dark::accentPressed;

    // Misc
    c[ImGuiCol_TextSelectedBg]       = ImVec4(Dark::accent.x, Dark::accent.y, Dark::accent.z, 0.35f);
    c[ImGuiCol_NavHighlight]         = Dark::accent;
    c[ImGuiCol_ModalWindowDimBg]     = ImVec4(0, 0, 0, 0.55f);
}

// ---- Component helpers -----------------------------------------------------

// Existing floating menu toggle.
inline bool PrimaryButton(const char* label, ImVec2 size = ImVec2(0, 40)) {
    const float hover = KennyMotion::Hover(ImGui::GetID(label), size);
    const ImVec4 surface = KennyMotion::Mix(Dark::accent, Dark::accentPressed, hover);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, size.y*0.5f);
    ImGui::PushStyleColor(ImGuiCol_Button,        surface);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, surface);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive,  Dark::accentPressed);
    ImGui::PushStyleColor(ImGuiCol_Text,          Dark::textPrimary);
    bool r = ImGui::Button(label, size);
    ImGui::PopStyleColor(4);
    ImGui::PopStyleVar();
    return r;
}

// Outlined neutral button.
inline bool SecondaryButton(const char* label, ImVec2 size = ImVec2(0, 40)) {
    ImGui::PushStyleColor(ImGuiCol_Button,        ImVec4(0, 0, 0, 0));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, Dark::surfaceSubtle);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive,  Hex(0x442029));
    ImGui::PushStyleColor(ImGuiCol_Text,          Dark::textPrimary);
    ImGui::PushStyleColor(ImGuiCol_Border,        Dark::outline);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
    bool r = ImGui::Button(label, size);
    ImGui::PopStyleVar();
    ImGui::PopStyleColor(5);
    return r;
}

// Horizontal primary tab. The menu draws its shared selection underline.
inline bool NavItem(const char* label, bool selected, ImVec2 size) {
    const ImGuiID id = ImGui::GetID(label);
    const float hover = KennyMotion::Hover(id, size);
    const float active = KennyMotion::Sample(id, 2, selected ? 1.0f : 0.0f);
    const ImVec4 surface = Hex(0x26171B, hover * 0.65f);
    // Explicit tab widths supply spacing; keep text padding small on mobile.
    const ImVec2 padding = ImGui::GetStyle().FramePadding;
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(padding.x * 0.25f, padding.y));
    ImGui::PushStyleColor(ImGuiCol_Button, surface);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, surface);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive,  Dark::accentSubtle);
    ImGui::PushStyleColor(ImGuiCol_Text,
        KennyMotion::Mix(Dark::textSecondary, Dark::accentPressed, active));
    bool r = ImGui::Button(label, size);
    ImGui::PopStyleColor(4);
    ImGui::PopStyleVar();
    return r;
}

// Rounded secondary tab; uses ImGui::Button for the full interactive hit area.
inline bool PillTab(const char* label, bool selected, ImVec2 size) {
    const ImGuiID id = ImGui::GetID(label);
    const float hover = KennyMotion::Hover(id, size);
    const float active = KennyMotion::Sample(id, 2, selected ? 1.0f : 0.0f);
    const ImVec4 surface = KennyMotion::Mix(
        KennyMotion::Mix(Hex(0x100B0E, 0.6f), Dark::accentSubtle, active),
        Hex(0x42202A, 0.9f), hover * 0.5f);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, size.y * 0.5f);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
    ImGui::PushStyleColor(ImGuiCol_Button, surface);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, surface);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, Dark::accentSubtle);
    ImGui::PushStyleColor(ImGuiCol_Border, KennyMotion::Mix(Dark::outline, Hex(0xC44551, 0.75f), std::max(active,hover)));
    ImGui::PushStyleColor(ImGuiCol_Text, KennyMotion::Mix(Dark::textSecondary, Dark::textPrimary, std::max(active,hover)));
    const bool pressed = ImGui::Button(label, size);
    ImGui::PopStyleColor(5);
    ImGui::PopStyleVar(2);
    return pressed;
}

// Sentence-case section header in textSecondary.
inline void SectionHeader(const char* title) {
    ImGui::Dummy(ImVec2(0, 4));
    ImGui::PushStyleColor(ImGuiCol_Text, Dark::textSecondary);
    ImGui::TextUnformatted(title);
    ImGui::PopStyleColor();
    ImGui::Dummy(ImVec2(0, 2));
}

} // namespace Claude
