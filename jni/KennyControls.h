#pragma once
#include <algorithm>
#include <cmath>
#include <type_traits>
#include "ClaudeTheme.h"
#include "imgui/imgui_internal.h"

namespace KennyControls {

inline float Scale() { return ImGui::GetFontSize() / 32.0f; }

// Native ImGui owns IDs, label hit areas, focus, edits, and input semantics.
// Only its square artwork is replaced by a circle on the same registered item.
inline bool Checkbox(const char* label, bool* value) {
    const float size = std::max(36.0f, ImGui::GetFrameHeight());
    const ImVec2 padding = ImGui::GetStyle().FramePadding;
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding,
                        ImVec2(padding.x, (size - ImGui::GetFontSize()) * 0.5f));
    for (ImGuiCol color : {ImGuiCol_FrameBg, ImGuiCol_FrameBgHovered,
                          ImGuiCol_FrameBgActive, ImGuiCol_CheckMark, ImGuiCol_Border,
                          ImGuiCol_NavHighlight})
        ImGui::PushStyleColor(color, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleColor(ImGuiCol_Text, *value ? Claude::Dark::textPrimary : Claude::Dark::textSecondary);
    const bool changed = ImGui::Checkbox(label, value);
    ImGui::PopStyleColor(7);
    ImGui::PopStyleVar();
    if (ImGui::IsItemVisible()) {
        const ImVec2 p = ImGui::GetItemRectMin();
        const ImVec2 center(p.x + size * 0.5f, p.y + size * 0.5f);
        const float radius = size * 0.46f;
        const bool hover = ImGui::IsItemHovered();
        ImDrawList* draw = ImGui::GetWindowDrawList();
        if (*value)
            draw->AddCircle(center, radius + 2.0f * Scale(),
                            ImGui::GetColorU32(Claude::Hex(0xFF5A5F, hover ? 0.24f : 0.12f)), 32, 2.0f);
        draw->AddCircleFilled(center, radius, ImGui::GetColorU32(*value ?
                              (hover ? Claude::Dark::accentPressed : Claude::Dark::accent) :
                              Claude::Dark::surfaceElev), 32);
        draw->AddCircle(center, radius, ImGui::GetColorU32(hover || ImGui::IsItemFocused() ?
                        Claude::Dark::accentPressed : Claude::Dark::outline), 32, 1.0f);
        if (*value) {
            const float mark = radius * 1.05f;
            ImGui::RenderCheckMark(draw, ImVec2(center.x - mark * 0.5f, center.y - mark * 0.5f),
                                  ImGui::GetColorU32(Claude::Dark::textPrimary), mark);
        }
    }
    return changed;
}

template <typename T>
inline bool Slider(const char* label, T* value, T minimum, T maximum, const char* format) {
    constexpr bool integer = std::is_same<T, int>::value;
    const ImGuiDataType type = integer ? ImGuiDataType_S32 : ImGuiDataType_Float;
    const ImGuiID id = ImGui::GetID(label);
    const float scale = Scale();
    const float width = ImGui::CalcItemWidth();
    const float line = ImGui::GetTextLineHeight();
    char number[64];
    ImGui::DataTypeFormatString(number, sizeof(number), type, value, format);
    const ImVec2 p = ImGui::GetCursorScreenPos();
    const float valueWidth = ImGui::CalcTextSize(number).x;
    const bool wrap = ImGui::CalcTextSize(label).x + valueWidth + 14.0f * scale > width;
    ImGui::BeginGroup();
    ImGui::GetWindowDrawList()->AddText(p, ImGui::GetColorU32(Claude::Dark::textSecondary), label);
    ImGui::GetWindowDrawList()->AddText(ImVec2(p.x + width - valueWidth, p.y + (wrap ? line : 0)),
                                       ImGui::GetColorU32(Claude::Dark::textPrimary), number);
    ImGui::Dummy(ImVec2(width, line * (wrap ? 2.0f : 1.0f)));

    const float height = std::max(36.0f, 36.0f * scale);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding,
                        ImVec2(ImGui::GetStyle().FramePadding.x, (height - line) * 0.5f));
    ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, std::max(12.0f, 18.0f * scale));
    const bool input = ImGui::TempInputIsActive(id) || ImGui::GetIO().KeyCtrl;
    for (ImGuiCol color : {ImGuiCol_FrameBg, ImGuiCol_FrameBgHovered,
                          ImGuiCol_FrameBgActive, ImGuiCol_SliderGrab, ImGuiCol_SliderGrabActive})
        ImGui::PushStyleColor(color, ImVec4(0, 0, 0, 0));
    if (!input) ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 0, 0, 0));
    // Empty visible label avoids a second label outside the track. Override the
    // ID seed with the caller's original label ID to retain native input state.
    ImGui::PushOverrideID(id);
    const bool changed = ImGui::SliderScalar("", type, value, &minimum, &maximum, format);
    ImGui::PopID();
    const ImVec2 a = ImGui::GetItemRectMin();
    const ImVec2 b = ImGui::GetItemRectMax();
    const bool active = ImGui::IsItemActive();
    const bool hover = ImGui::IsItemHovered();
    if (!input) ImGui::PopStyleColor();
    ImGui::PopStyleColor(5);
    if (!ImGui::TempInputIsActive(id) && ImGui::IsItemVisible()) {
        // Match native SliderBehavior's linear grab geometry, including the
        // wider discrete grab on integer sliders. Values/ranges are untouched.
        const float sliderSize = b.x - a.x - 4.0f;
        const double range = static_cast<double>(maximum) - static_cast<double>(minimum);
        float grab = ImGui::GetStyle().GrabMinSize;
        if (integer && range >= 0)
            grab = std::max(grab, sliderSize / static_cast<float>(range + 1.0));
        grab = std::min(grab, sliderSize);
        const float left = a.x + 2.0f + grab * 0.5f;
        const float right = b.x - 2.0f - grab * 0.5f;
        const float ratio = range > 0 ? static_cast<float>(std::clamp(
            (static_cast<double>(*value) - minimum) / range, 0.0, 1.0)) : 0.0f;
        const float x = left + (right - left) * ratio;
        const float y = (a.y + b.y) * 0.5f;
        const float track = std::max(3.0f, 6.0f * scale);
        ImDrawList* draw = ImGui::GetWindowDrawList();
        draw->AddRectFilled(ImVec2(left, y - track * 0.5f), ImVec2(right, y + track * 0.5f),
                            ImGui::GetColorU32(Claude::Dark::surfaceSubtle), track * 0.5f);
        draw->AddRectFilled(ImVec2(left, y - track * 0.5f), ImVec2(x, y + track * 0.5f),
                            ImGui::GetColorU32(Claude::Dark::accent), track * 0.5f);
        const float radius = std::max(7.0f, 10.0f * scale);
        if (active || hover)
            draw->AddCircle(ImVec2(x, y), radius + 3.0f,
                            ImGui::GetColorU32(Claude::Hex(0xFF5A5F, 0.18f)), 24, 2.0f);
        draw->AddCircleFilled(ImVec2(x, y), radius,
                              ImGui::GetColorU32(active || hover ? Claude::Dark::accentPressed : Claude::Dark::accent), 24);
        draw->AddCircle(ImVec2(x, y), radius, ImGui::GetColorU32(Claude::Dark::accentPressed), 24, 1.0f);
    }
    ImGui::PopStyleVar(2);
    ImGui::EndGroup();
    return changed;
}

inline bool SliderFloat(const char* label, float* value, float minimum, float maximum,
                        const char* format = "%.3f") { return Slider(label, value, minimum, maximum, format); }
inline bool SliderInt(const char* label, int* value, int minimum, int maximum,
                      const char* format = "%d") { return Slider(label, value, minimum, maximum, format); }

} // namespace KennyControls
