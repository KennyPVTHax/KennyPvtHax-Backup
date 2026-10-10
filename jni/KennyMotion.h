#pragma once
#include <algorithm>
#include <array>
#include <cmath>
#include "imgui/imgui.h"

// Presentation state only. Native widgets continue to update their values on
// the activation frame; this cache never owns configuration or input state.
namespace KennyMotion {
inline float Delta(float dt) {
    return std::isfinite(dt) ? std::clamp(dt, 0.0f, 0.1f) : 0.0f;
}
inline float Step(float from, float to, float rate, float dt) {
    return from + (to - from) * (1.0f - std::exp(-rate * Delta(dt)));
}
inline ImVec4 Mix(const ImVec4& a, const ImVec4& b, float t) {
    return ImVec4(a.x + (b.x-a.x)*t, a.y + (b.y-a.y)*t,
                  a.z + (b.z-a.z)*t, a.w + (b.w-a.w)*t);
}
struct Entry { ImGuiID id = 0; unsigned channel = 0; int frame = -2; float value = 0; };
constexpr unsigned Capacity = 192;
struct Cache {
    std::array<Entry, Capacity> entries{};
    ImGuiContext* context = nullptr;
    float Sample(ImGuiID id, unsigned channel, float target, float rate, bool snap = false) {
        if (context != ImGui::GetCurrentContext()) {
            entries = {};
            context = ImGui::GetCurrentContext();
        }
        const int frame = ImGui::GetFrameCount();
        const unsigned first = (id ^ (channel * 2654435761u)) % Capacity;
        Entry* slot = &entries[first];
        for (unsigned i = 0; i < Capacity; ++i) {
            Entry& candidate = entries[(first+i) % Capacity];
            if (candidate.id == id && candidate.channel == channel) { slot = &candidate; break; }
            if (!candidate.id) { slot = &candidate; break; }
            if (candidate.frame < slot->frame) slot = &candidate;
        }
        target = std::isfinite(target) ? target : 0.0f;
        if (snap || slot->id != id || slot->channel != channel || slot->frame < frame-1)
            slot->value = target; // Newly visible controls never inherit stale animation.
        else if (slot->frame != frame)
            slot->value = Step(slot->value, target, rate, ImGui::GetIO().DeltaTime);
        slot->id = id; slot->channel = channel; slot->frame = frame;
        return slot->value;
    }
};
inline Cache cache;
inline float Sample(ImGuiID id, unsigned channel, float target, float rate = 18.0f, bool snap = false) {
    return cache.Sample(id, channel, target, rate, snap);
}
// Prediction is used only for artwork. ButtonBehavior still decides activation,
// keyboard focus, disabled behavior, and whether another window blocks input.
inline float Hover(ImGuiID id, ImVec2 size) {
    const ImVec2 p = ImGui::GetCursorScreenPos();
    const bool hover = ImGui::IsWindowHovered() &&
        ImGui::IsMouseHoveringRect(p, ImVec2(p.x+size.x, p.y+size.y));
    return Sample(id, 1, hover ? 1.0f : 0.0f);
}
} // namespace KennyMotion
