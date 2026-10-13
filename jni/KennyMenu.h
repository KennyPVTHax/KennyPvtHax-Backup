#pragma once
#include <algorithm>
#include <cmath>
#include "ClaudeTheme.h"
#include "ANOY/font_awesome_5.h"

// Application-owned window chrome. Feature controls are supplied by main.cpp;
// this layer does not depend on the game SDK, platform hooks, or configuration.
namespace KennyMenu {

enum class Category { Visual, Aim, Misc, Style, Settings };

// Recovery uses the original embedded font atlas without adding fonts.

struct State {
    Category category = Category::Visual;
    int visualTab = 1;
    int miscTab = 4;
    bool initialized = false;

    void Select(Category next, int& tab) {
        category = next;
        switch (next) {
        case Category::Visual: tab = visualTab; break;
        case Category::Aim: tab = 3; break;
        case Category::Misc: tab = miscTab; break;
        default: break; // Reserved containers never create backend tab values.
        }
    }

    void Initialize(int tab) {
        if (initialized) return;
        if (tab == 2) visualTab = 2;
        if (tab == 5) miscTab = 5;
        if (tab == 3) category = Category::Aim;
        if (tab == 4 || tab == 5) category = Category::Misc;
        initialized = true;
    }
};

struct Layout {
    ImVec2 size;
    float scale, padding, header, secondary, brand, navY, navHeight;
    bool compact;
};

inline Layout Measure(ImVec2 viewport) {
    Layout l{};
    l.scale = std::clamp(std::min(viewport.y / 872.0f, viewport.x / 1440.0f), 0.55f, 1.5f);
    l.padding = 26.0f * l.scale;
    const float margin = std::max(8.0f, 12.0f * l.scale);
    l.size = ImVec2(std::min(viewport.x - 2.0f * margin,
                           std::max(viewport.x * 0.59f, 760.0f * l.scale)),
                    viewport.y * 0.82f);
    l.compact = l.size.x < 960.0f * l.scale;
    l.brand = 220.0f * l.scale;
    l.navY = l.compact ? std::max(36.0f, 56.0f * l.scale) : 0.0f;
    l.navHeight = l.compact ? std::max(44.0f, 64.0f * l.scale) : 100.0f * l.scale;
    l.header = l.navY + l.navHeight;
    l.secondary = std::max(48.0f, 74.0f * l.scale);
    return l;
}

inline ImVec2 Constrain(ImVec2 pos, ImVec2 size, ImVec2 viewport) {
    return ImVec2(std::clamp(pos.x, 0.0f, std::max(0.0f, viewport.x - size.x)),
                  std::clamp(pos.y, 0.0f, std::max(0.0f, viewport.y - size.y)));
}

template <typename RenderPanel>
inline void Draw(State& state, bool& opened, int& tab, ImVec2 viewport, RenderPanel renderPanel) {
    if (viewport.x <= 0.0f || viewport.y <= 0.0f) return;
    state.Initialize(tab);
    const Layout l = Measure(viewport);
    ImGui::SetNextWindowSize(l.size, ImGuiCond_Always);
    ImGui::SetNextWindowPos(ImVec2((viewport.x - l.size.x) * 0.5f,
                                 (viewport.y - l.size.y) * 0.5f), ImGuiCond_FirstUseEver);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, Claude::RadiusWindow * l.scale);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(12.0f * l.scale, 7.0f * l.scale));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8.0f * l.scale, 12.0f * l.scale));
    ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarSize, std::max(8.0f, 8.0f * l.scale));
    const ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar;
    if (ImGui::Begin("KennyPvtHax", nullptr, flags)) {
        // Per-window scale is assigned, never multiplied into global style/fonts.
        ImGui::SetWindowFontScale(2.0f * l.scale);
        const ImVec2 pos = ImGui::GetWindowPos();
        const ImVec2 bounded = Constrain(pos, l.size, viewport);
        if (pos.x != bounded.x || pos.y != bounded.y) ImGui::SetWindowPos(bounded);

        const float closeSize = std::max(36.0f, 44.0f * l.scale);
        const float brandHeight = l.compact ? l.navY : l.header;
        ImGui::SetCursorPos(ImVec2(l.padding, 0));
        ImGui::InvisibleButton("##header-drag", ImVec2(l.brand, brandHeight));
        if (ImGui::IsItemActive() && ImGui::IsMouseDragging(0)) {
            const ImVec2 current = ImGui::GetWindowPos();
            const ImVec2 delta = ImGui::GetIO().MouseDelta;
            ImGui::SetWindowPos(Constrain(ImVec2(current.x + delta.x, current.y + delta.y), l.size, viewport));
        }
        if (ImGui::IsItemHovered()) ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);
        const ImVec2 origin = ImGui::GetWindowPos();
        ImDrawList* draw = ImGui::GetWindowDrawList();
        const char* brand = "KennyPvtHax";
        const ImVec2 brandText = ImGui::CalcTextSize(brand);
        draw->AddText(ImVec2(origin.x + l.padding, origin.y + (brandHeight - brandText.y) * 0.5f),
                      ImGui::GetColorU32(Claude::Dark::accentPressed), brand);

        ImGui::SetCursorPos(ImVec2(l.size.x - l.padding - closeSize,
                                  (brandHeight - closeSize) * 0.5f));
        if (Claude::NavItem(ICON_FA_TIMES "##close", false, ImVec2(closeSize, closeSize))) opened = false;

        const float navX = l.compact ? l.padding : l.padding + l.brand;
        const float navRight = l.compact ? l.size.x - l.padding : l.size.x - l.padding - closeSize;
        const float tabWidth = (navRight - navX) / 5.0f;
        const char* labels[] = { ICON_FA_EYE "  Visual", ICON_FA_CROSSHAIRS "  Aim",
            ICON_FA_CUBE "  Misc", ICON_FA_PALETTE "  Style", ICON_FA_COG "  Settings" };
        for (int i = 0; i < 5; ++i) {
            ImGui::SetCursorPos(ImVec2(navX + i * tabWidth, l.navY + 4.0f * l.scale));
            if (Claude::NavItem(labels[i], static_cast<int>(state.category) == i,
                               ImVec2(tabWidth, l.navHeight - 12.0f * l.scale)))
                state.Select(static_cast<Category>(i), tab);
        }
        // One bounded, time-based underline; no per-tab animation allocations.
        const float target = static_cast<float>(static_cast<int>(state.category));
        const float underlineWidth = std::min(78.0f * l.scale, tabWidth * 0.65f);
        const float underlineX = origin.x + navX + (target + 0.5f) * tabWidth - underlineWidth * 0.5f;
        draw->AddRectFilled(ImVec2(underlineX, origin.y + l.header - 9.0f * l.scale),
                            ImVec2(underlineX + underlineWidth, origin.y + l.header - 6.0f * l.scale),
                            ImGui::GetColorU32(Claude::Dark::accentPressed), 2.0f * l.scale);
        const ImU32 divider = ImGui::GetColorU32(Claude::Hex(0x7A1C24, 0.32f));
        draw->AddLine(ImVec2(origin.x + 1, origin.y + l.header),
                      ImVec2(origin.x + l.size.x - 1, origin.y + l.header), divider);

        const char* secondary[2] = {};
        int values[2] = {};
        int count = 1;
        switch (state.category) {
        case Category::Visual: secondary[0] = "Player ESP"; secondary[1] = "World ESP"; values[0] = 1; values[1] = 2; count = 2; break;
        case Category::Aim: secondary[0] = "Aimbot"; values[0] = 3; break;
        case Category::Misc: secondary[0] = "Bullet track"; secondary[1] = "Extra features"; values[0] = 4; values[1] = 5; count = 2; break;
        case Category::Style: secondary[0] = "Appearance"; break;
        case Category::Settings: secondary[0] = "General"; break;
        }
        const float gap = 10.0f * l.scale;
        const float pillHeight = std::max(36.0f, 46.0f * l.scale);
        float widths[2] = {};
        float total = gap * (count - 1);
        for (int i = 0; i < count; ++i) {
            widths[i] = ImGui::CalcTextSize(secondary[i]).x + 36.0f * l.scale;
            total += widths[i];
        }
        float x = (l.size.x - total) * 0.5f;
        for (int i = 0; i < count; ++i) {
            ImGui::SetCursorPos(ImVec2(x, l.header + (l.secondary - pillHeight) * 0.5f));
            const bool reserved = state.category == Category::Style || state.category == Category::Settings;
            if (Claude::PillTab(secondary[i], reserved || tab == values[i], ImVec2(widths[i], pillHeight)) && !reserved) {
                tab = values[i];
                if (state.category == Category::Visual) state.visualTab = tab;
                if (state.category == Category::Misc) state.miscTab = tab;
            }
            x += widths[i] + gap;
        }
        const float contentY = l.header + l.secondary;
        draw->AddLine(ImVec2(origin.x + 1, origin.y + contentY),
                      ImVec2(origin.x + l.size.x - 1, origin.y + contentY), divider);

        // Isolate content scrolling from both navigation rows. No nested card border.
        ImGui::SetCursorPos(ImVec2(l.padding, contentY + 18.0f * l.scale));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::PushStyleColor(ImGuiCol_ChildBg, Claude::Hex(0x1A1012, 0.16f));
        if (ImGui::BeginChild("##content", ImVec2(l.size.x - 2.0f * l.padding,
                             l.size.y - contentY - 36.0f * l.scale), false)) {
            // This ImGui version multiplies a child's scale by its parent's.
            ImGui::SetWindowFontScale(0.875f);
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8.0f * l.scale, 10.0f * l.scale));
            ImGui::PushItemWidth(std::min(420.0f * l.scale, ImGui::GetContentRegionAvail().x * 0.58f));
            if (state.category == Category::Style || state.category == Category::Settings) {
                Claude::SectionHeader(state.category == Category::Style ? "Appearance" : "General");
                ImGui::TextDisabled("Appearance preferences are deferred until Stage 2 passes device testing.");
            } else {
                renderPanel();
            }
            ImGui::PopItemWidth();
            ImGui::PopStyleVar();
        }
        ImGui::EndChild();
        ImGui::PopStyleColor();
        ImGui::PopStyleVar();
    }
    ImGui::End();
    ImGui::PopStyleVar(5);
}

} // namespace KennyMenu
