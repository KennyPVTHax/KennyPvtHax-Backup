#pragma once
#include "KennyControls.h"

namespace KennyPanels {

inline bool Begin(const char* id, int maximumColumns, float minimumEm = 10.0f) {
    const float width = ImGui::GetContentRegionAvail().x;
    const int columns = std::clamp(static_cast<int>(width / (ImGui::GetFontSize() * minimumEm)), 1, maximumColumns);
    ImGui::PushStyleVar(ImGuiStyleVar_CellPadding,
                        ImVec2(14.0f * KennyControls::Scale(), 10.0f * KennyControls::Scale()));
    ImGui::PushStyleColor(ImGuiCol_TableBorderLight, Claude::Hex(0x7A1C24, 0.3f));
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
    ImGui::GetWindowDrawList()->AddLine(p, ImVec2(p.x + width, p.y),
                                       ImGui::GetColorU32(Claude::Dark::outline));
    ImGui::GetWindowDrawList()->AddLine(p, ImVec2(p.x + 18.0f * KennyControls::Scale(), p.y),
                                       ImGui::GetColorU32(Claude::Dark::accentPressed), 2.0f);
    ImGui::Dummy(ImVec2(0, 6.0f * KennyControls::Scale()));
}

inline void EndSection() { ImGui::PopItemWidth(); }
inline void End() { ImGui::EndTable(); ImGui::PopStyleColor(); ImGui::PopStyleVar(); }

} // namespace KennyPanels
