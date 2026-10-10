#pragma once
#include <algorithm>
#include <cmath>
#include <string>

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
    bool uiSounds = true;
    float uiVolume = 35.0f;
    std::string characterId="highschool_dxd_rias",voicePack="default",characterArtwork="character.png";
    bool characterVoice=true,characterLauncher=true;
    float characterVolume=70;
    int soundProfile = 0; // 0: theme, 1: Aurora soft, 2: Classic crisp.
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
    p.uiVolume=Bounded(p.uiVolume,0,100,35);
    p.soundProfile=std::clamp(p.soundProfile,0,2);
    auto token=[](const std::string& s){if(s.empty()||s.size()>63)return false;for(char c:s)if(!((c>='a'&&c<='z')||(c>='0'&&c<='9')||c=='_'||c=='-'))return false;return true;};
    if(!token(p.characterId))p.characterId="highschool_dxd_rias";
    if(!token(p.voicePack))p.voicePack="default";
    bool artworkValid=!p.characterArtwork.empty()&&p.characterArtwork.size()<=63&&p.characterArtwork.front()!='/'&&p.characterArtwork.back()!='/'&&p.characterArtwork.find("..") == std::string::npos;
    for(char c:p.characterArtwork)artworkValid&=(c>='a'&&c<='z')||(c>='0'&&c<='9')||c=='_'||c=='-'||c=='.'||c=='/';
    if(!artworkValid)p.characterArtwork="character.png";
    p.characterVolume=Bounded(p.characterVolume,0,100,70);
}
inline bool Equal(const Preferences& a, const Preferences& b) {
    return a.theme==b.theme && a.opacity==b.opacity && a.compactRows==b.compactRows &&
        a.reducedMotion==b.reducedMotion && a.auroraIntensity==b.auroraIntensity &&
        a.particleActivity==b.particleActivity && a.starsVisible==b.starsVisible &&
        a.touchAttraction==b.touchAttraction && a.artworkDim==b.artworkDim && a.artworkCover==b.artworkCover &&
        a.uiSounds==b.uiSounds && a.uiVolume==b.uiVolume && a.soundProfile==b.soundProfile && a.characterId==b.characterId && a.voicePack==b.voicePack &&
        a.characterArtwork==b.characterArtwork && a.characterVoice==b.characterVoice &&
        a.characterLauncher==b.characterLauncher && a.characterVolume==b.characterVolume;
}
} // namespace KennyAppearance
