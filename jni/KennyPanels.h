#pragma once
#include "KennyControls.h"

namespace KennyPanels {

inline bool Begin(const char* id, int maximumColumns, float minimumEm = 10.0f,
                  const char* widestCheckbox = nullptr) {
    const float width = ImGui::GetContentRegionAvail().x;
    float minimumWidth = ImGui::GetFontSize() * minimumEm;
    if (widestCheckbox) {
        const float controlWidth = ImGui::CalcTextSize(widestCheckbox).x +
            std::max(36.0f, ImGui::GetFrameHeight()) + ImGui::GetStyle().ItemInnerSpacing.x;
        minimumWidth = std::max(minimumWidth, controlWidth + 28.0f * KennyControls::Scale() + 1.0f);
    }
    const int columns = std::clamp(static_cast<int>(width / minimumWidth), 1, maximumColumns);
    ImGui::PushStyleVar(ImGuiStyleVar_CellPadding,
                        ImVec2(14.0f * KennyControls::Scale(), 10.0f * KennyControls::Scale()));
    ImGui::PushStyleColor(ImGuiCol_TableBorderLight, Claude::Hex(0x73636A, 0.13f));
    const bool visible = ImGui::BeginTable(id, columns, ImGuiTableFlags_SizingStretchSame |
                                         ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_NoSavedSettings);
    if (!visible) { ImGui::PopStyleColor(); ImGui::PopStyleVar(); }
    return visible;
}

inline void Section(const char* label) {
    ImGui::TableNextColumn();
    ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x);
    // Match the minimum touch target's text baseline, including small screens.
    // Tables carry this baseline between cells, so set it before each heading.
    const ImVec2 padding = ImGui::GetStyle().FramePadding;
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding,
                        ImVec2(padding.x, std::max(padding.y, (36.0f - ImGui::GetFontSize()) * 0.5f)));
    ImGui::AlignTextToFramePadding();
    ImGui::TextColored(Claude::Dark::textPrimary, "%s", label);
    ImGui::PopStyleVar();
    const ImVec2 p = ImGui::GetCursorScreenPos();
    const float width = ImGui::GetContentRegionAvail().x;
    const ImU32 start=ImGui::GetColorU32(Claude::Hex(0x88717B,0.24f)),clear=ImGui::GetColorU32(Claude::Hex(0x88717B,0));
    ImGui::GetWindowDrawList()->AddRectFilledMultiColor(p,ImVec2(p.x+width,p.y+1),start,clear,clear,start);
    KennyPaint::Seam(ImGui::GetWindowDrawList(),p,28*KennyControls::Scale(),Claude::Hex(0xE78695,0.62f),1);
    ImGui::Dummy(ImVec2(0, 6.0f * KennyControls::Scale()));
}

inline void EndSection() { ImGui::PopItemWidth(); }
inline void End() { ImGui::EndTable(); ImGui::PopStyleColor(); ImGui::PopStyleVar(); }

inline void Note(const char* text) {
    ImGui::PushStyleColor(ImGuiCol_Text, Claude::Dark::textSecondary);
    ImGui::TextWrapped("%s", text);
    ImGui::PopStyleColor();
}

} // namespace KennyPanels
