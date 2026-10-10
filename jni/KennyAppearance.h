#pragma once
#include "KennyPanels.h"

// Session-only presentation state. No feature configuration, persistence keys,
// SDK calls, or platform behavior are owned by these panels.
namespace KennyAppearance {

struct Preferences {
    float opacity = 97.0f;
    bool compactRows = false;
};

inline void DrawStyle(Preferences& preferences) {
    if (!KennyPanels::Begin("##appearance", 2, 12.0f)) return;
    KennyPanels::Section("Surface");
    KennyControls::SliderFloat("Menu opacity", &preferences.opacity, 85.0f, 100.0f, "%.0f%%");
    // Bound presentation-only numeric entry, without altering feature sliders.
    preferences.opacity = std::clamp(preferences.opacity, 85.0f, 100.0f);
    KennyPanels::Note("Adjust the dark menu surface. Text and controls stay clear.");
    KennyPanels::EndSection();
    KennyPanels::Section("Layout");
    KennyControls::Choice("Row spacing", &preferences.compactRows, "Standard", "Compact");
    KennyPanels::Note("Changes apply immediately and last until restart.");
    KennyPanels::EndSection();
    KennyPanels::End();
}

inline void DrawSettings(Preferences& preferences, bool& centerRequested) {
    if (!KennyPanels::Begin("##general", 2, 12.0f)) return;
    KennyPanels::Section("Menu");
    if (KennyControls::Button("Center window")) centerRequested = true;
    if (KennyControls::Button("Reset appearance")) preferences = Preferences{};
    KennyPanels::Note("Restore the default menu opacity and row spacing.");
    KennyPanels::EndSection();
    KennyPanels::Section("About");
    ImGui::TextUnformatted("KennyPvtHax");
    KennyPanels::Note("Crimson / Fire Red");
    KennyPanels::Note("Android landscape interface");
    KennyPanels::EndSection();
    KennyPanels::End();
}

} // namespace KennyAppearance
