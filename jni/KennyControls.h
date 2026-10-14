#pragma once
#include <algorithm>
#include <cmath>
#include <type_traits>
#include "ClaudeTheme.h"
#include "KennyAudio.h"
#include "imgui/imgui_internal.h"

namespace KennyControls {

inline float Scale() { return ImGui::GetFontSize() / 32.0f; }

// Full-width action with the same rounded artwork as secondary navigation.
// The native button owns activation and retains the caller's label ID.
inline bool Button(const char* label,bool emitSound=true) {
    const bool pressed=Claude::PillTab(label, false, ImVec2(ImGui::GetContentRegionAvail().x,
                                              std::max(36.0f, ImGui::GetFrameHeight())));
    if(pressed&&emitSound)KennyAudio::Emit(KennyAudio::Event::ButtonPressed);
    return pressed;
}

inline bool Choice(const char* label, bool* value, const char* first, const char* second) {
    ImGui::BeginGroup();
    ImGui::TextUnformatted(label);
    const float gap = ImGui::GetStyle().ItemSpacing.x;
    const float width = (ImGui::GetContentRegionAvail().x - gap) * 0.5f;
    const float height = std::max(36.0f, ImGui::GetFrameHeight());
    bool changed = false;
    ImGui::PushID(label);
    if (Claude::PillTab(first, !*value, ImVec2(width, height)) && *value) {
        *value = false;
        changed = true;
    }
    ImGui::SameLine(0, gap);
    if (Claude::PillTab(second, *value, ImVec2(width, height)) && !*value) {
        *value = true;
        changed = true;
    }
    ImGui::PopID();
    ImGui::EndGroup();
    if(changed)KennyAudio::Emit(KennyAudio::Event::ButtonPressed);
    return changed;
}

// Native ImGui owns IDs, label hit areas, focus, edits, and input semantics.
// Only its square artwork is replaced by a circle on the same registered item.
inline bool Checkbox(const char* label, bool* value) {
    const ImGuiID id = ImGui::GetID(label);
    const float size = std::max(36.0f, ImGui::GetFrameHeight());
    const ImVec2 padding = ImGui::GetStyle().FramePadding;
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding,
                        ImVec2(padding.x, (size - ImGui::GetFontSize()) * 0.5f));
    for (ImGuiCol color : {ImGuiCol_FrameBg, ImGuiCol_FrameBgHovered,
                          ImGuiCol_FrameBgActive, ImGuiCol_CheckMark, ImGuiCol_Border,
                          ImGuiCol_NavHighlight})
        ImGui::PushStyleColor(color, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleColor(ImGuiCol_Text, *value ? Claude::Dark::textPrimary : Claude::Dark::textSecondary);
    const bool oldState=*value;
    const bool changed = ImGui::Checkbox(label, value);
    if(changed && oldState!=*value)KennyAudio::Emit(*value ? KennyAudio::Event::CheckboxOn : KennyAudio::Event::CheckboxOff,label);
    ImGui::PopStyleColor(7);
    ImGui::PopStyleVar();
    if (ImGui::IsItemVisible()) {
        const ImVec2 p = ImGui::GetItemRectMin();
        const ImVec2 center(p.x + size * 0.5f, p.y + size * 0.5f);
        const float radius = size * 0.46f;
        const bool hover = ImGui::IsItemHovered();
        const float checked = KennyMotion::Sample(id, 3, *value ? 1.0f : 0.0f, 22.0f);
        const float emphasis = KennyMotion::Sample(id, 1, hover || ImGui::IsItemFocused() ? 1.0f : 0.0f);
        ImDrawList* draw = ImGui::GetWindowDrawList();
        KennyPaint::Disc(draw,center,radius,
            KennyMotion::Mix(Claude::Hex(0x241B21),KennyMotion::Mix(Claude::Hex(0xD72A45),Claude::Dark::accentPressed,emphasis),checked),
            KennyMotion::Mix(Claude::Hex(0x0C0B0F),Claude::Hex(0xA40F29),checked));
        draw->AddCircle(center, radius, ImGui::GetColorU32(KennyMotion::Mix(
            Claude::Hex(0x88717B,0.42f), Claude::Hex(0xE592A0,0.72f), std::max(checked*0.45f,emphasis))), 32, 1.0f);
        if(checked>0.005f) {
            draw->PathArcTo(center,radius-1.4f,-2.4f,-0.75f,12);
            draw->PathStroke(ImGui::GetColorU32(Claude::Hex(0xFFD3DB,checked*0.20f)),false,1);
        }
        if (checked > 0.005f) {
            const float mark = radius * 1.05f;
            ImVec4 ink = Claude::Dark::textPrimary;
            ink.w *= checked;
            ImGui::RenderCheckMark(draw, ImVec2(center.x-mark*0.5f,center.y-mark*0.5f+0.8f),
                ImGui::GetColorU32(Claude::Hex(0x470D19,checked*0.45f)),mark);
            ImGui::RenderCheckMark(draw, ImVec2(center.x - mark * 0.5f, center.y - mark * 0.5f),
                                  ImGui::GetColorU32(ink), mark);
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
        // Active native input tracks the pointer exactly. Only inactive artwork
        // eases toward programmatic changes; numeric labels always show reality.
        const float visual = KennyMotion::Sample(id, 4, ratio, 24.0f, active || changed);
        const float emphasis = KennyMotion::Sample(id, 1, active || hover ? 1.0f : 0.0f);
        const float x = left + (right - left) * visual;
        const float y = (a.y + b.y) * 0.5f;
        const float track = std::max(3.0f, 6.0f * scale);
        ImDrawList* draw = ImGui::GetWindowDrawList();
        draw->AddRectFilled(ImVec2(left, y - track * 0.5f), ImVec2(right, y + track * 0.5f),
                            ImGui::GetColorU32(Claude::Dark::surfaceSubtle), track * 0.5f);
        draw->AddRectFilled(ImVec2(left, y - track * 0.5f), ImVec2(x, y + track * 0.5f),
                            ImGui::GetColorU32(Claude::Dark::accent), track * 0.5f);
        if(x-left>4) {
            draw->AddRectFilledMultiColor(ImVec2(left+1,y-track*0.3f),ImVec2(x-1,y+track*0.3f),
                ImGui::GetColorU32(Claude::Hex(0xC1122B)),ImGui::GetColorU32(Claude::Hex(0xEA4559)),
                ImGui::GetColorU32(Claude::Hex(0xD72840)),ImGui::GetColorU32(Claude::Hex(0xC1122B)));
        }
        const float radius = std::max(7.0f, 10.0f * scale);
        if (emphasis > 0.005f)
            draw->AddCircle(ImVec2(x, y), radius + 3.0f,
                            ImGui::GetColorU32(Claude::Hex(0xFF5664, 0.12f*emphasis)), 24, 2.0f);
        KennyPaint::Disc(draw,ImVec2(x,y),radius,
            KennyMotion::Mix(Claude::Hex(0xE86A7F),Claude::Hex(0xFFC2CC),emphasis),Claude::Hex(0xAD1E38));
        draw->AddCircle(ImVec2(x, y), radius, ImGui::GetColorU32(Claude::Hex(0xECA5B2,0.50f)), 24, 1.0f);
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
