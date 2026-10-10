#pragma once
#include <algorithm>
#include <cmath>

// UI-only preferences. These never reference feature/configuration variables.
namespace KennyAppearance {
enum class Theme { Aurora, Anime, Classic };
inline const char* ThemeName(Theme theme) {
    switch(theme) { case Theme::Anime: return "Anime"; case Theme::Classic: return "Classic";
    default: return "Aurora"; }
}
struct Preferences {
    Theme theme = Theme::Aurora;
    float opacity = 97.0f;
    bool compactRows = false, reducedMotion = false;
    float auroraIntensity = 100.0f, particleActivity = 100.0f;
    bool starsVisible = true, touchAttraction = true;
    float artworkDim = 70.0f;
    bool artworkCover = true;
};
inline float Bounded(float value, float low, float high, float fallback) {
    return std::isfinite(value) ? std::clamp(value,low,high) : fallback;
}
inline void Normalize(Preferences& p) {
    if(static_cast<int>(p.theme)<0 || static_cast<int>(p.theme)>2) p.theme=Theme::Aurora;
    p.opacity=Bounded(p.opacity,85,100,97);
    p.auroraIntensity=Bounded(p.auroraIntensity,0,100,100);
    p.particleActivity=Bounded(p.particleActivity,0,100,100);
    p.artworkDim=Bounded(p.artworkDim,35,95,70);
}
inline bool Equal(const Preferences& a, const Preferences& b) {
    return a.theme==b.theme && a.opacity==b.opacity && a.compactRows==b.compactRows &&
        a.reducedMotion==b.reducedMotion && a.auroraIntensity==b.auroraIntensity &&
        a.particleActivity==b.particleActivity && a.starsVisible==b.starsVisible &&
        a.touchAttraction==b.touchAttraction && a.artworkDim==b.artworkDim && a.artworkCover==b.artworkCover;
}
} // namespace KennyAppearance
