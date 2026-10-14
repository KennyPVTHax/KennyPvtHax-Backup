#pragma once
#include <algorithm>
#include <cmath>
#include "ClaudeTheme.h"
#include "KennyAppearance.h"
#include "KennyEffects.h"
#include "KennyAurora.h"
#include "KennyIdentity.h"
#include "KennyAppearanceStore.h"
#include "KennyThemeBackground.h"
#include "KennyElectricStarfield.h"
#include "imgui/imgui_internal.h"
#include "ANOY/font_awesome_5.h"

// Application-owned window chrome. Feature controls are supplied by main.cpp;
// this layer does not depend on the game SDK, platform hooks, or configuration.
namespace KennyMenu {

enum class Category { Visual, Aim, Misc, Style, Settings };

// A separately baked menu font keeps header glyphs sharp without changing the
// default font used by the floating toggle or existing overlay text.
inline ImFont* Font = nullptr;

struct State {
    Category category = Category::Visual;
    int visualTab = 1;
    int miscTab = 4;
    bool initialized = false;
    float indicator = -1.0f;
    KennyAppearance::Preferences appearance;
    KennyAppearance::Store storage;
    KennyThemeBackground::Artwork artwork;
    KennyCharacters::Registry characters;
    KennyAudio::Dispatcher* audio=nullptr;
    const char* audioStatus="UI audio unavailable in this host preview.";
    bool centerRequested = false;
    KennyEffects::State effects;
    KennyAurora::State aurora;
    KennyElectric::State electric;
    KennyThemeBackground::ArtworkFrame animeVideoFrame;
    const char* videoStatus="Native video playback unavailable in this host preview.";

    void Select(Category next, int& tab) {
        category = next;
        switch (next) {
        case Category::Visual: tab = visualTab; break;
        case Category::Aim: tab = 3; break;
        case Category::Misc: tab = miscTab; break;
        default: break; // Presentation panels never create backend tab values.
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
inline void Draw(State& state, bool& opened, int& tab, ImVec2 viewport, RenderPanel renderPanel, float presentationAlpha=1.0f, bool acceptInput=true) {
    if (viewport.x <= 0.0f || viewport.y <= 0.0f) return;
    state.Initialize(tab);
    state.characters.Prepare(state.appearance,state.audio);
    KennyAudio::Scope audio(state.audio,state.appearance,ImGui::GetTime());
    KennyAppearance::Normalize(state.appearance);
    KennyMotion::ScopedReduction motion(state.appearance.reducedMotion);
    const Layout l = Measure(viewport);
    if (Font) ImGui::PushFont(Font);
    ImGui::SetNextWindowSize(l.size, ImGuiCond_Always);
    ImGui::SetNextWindowPos(ImVec2((viewport.x - l.size.x) * 0.5f,
                                 (viewport.y - l.size.y) * 0.5f),
                            state.centerRequested ? ImGuiCond_Always : ImGuiCond_FirstUseEver);
    state.centerRequested = false;
    ImGui::PushStyleVar(ImGuiStyleVar_Alpha,ImGui::GetStyle().Alpha*std::clamp(presentationAlpha,0.0f,1.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, Claude::RadiusWindow * l.scale);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(12.0f * l.scale, 7.0f * l.scale));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8.0f * l.scale, 12.0f * l.scale));
    ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarSize, std::max(8.0f, 8.0f * l.scale));
    ImVec4 background = Claude::Dark::bg;
    background.w = std::clamp(state.appearance.opacity, 85.0f, 100.0f) * 0.01f;
    ImGui::PushStyleColor(ImGuiCol_WindowBg, background);
    const ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar |
        (acceptInput ? ImGuiWindowFlags_None : ImGuiWindowFlags_NoInputs);
    if (ImGui::Begin("KennyPvtHax", nullptr, flags)) {
        ImGui::BeginDisabled(!acceptInput);
        // Per-window scale is assigned, never multiplied into global style/fonts.
        ImGui::SetWindowFontScale((Font ? 1.0f : 2.0f) * l.scale);
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
        const bool resumed = state.effects.Advance(ImGui::GetFrameCount(), ImGui::GetIO().DeltaTime, state.appearance.reducedMotion);
        // Reused native channel buffers resolve input and the selected route
        // after widgets, yet paint its background behind them in this frame.
        draw->ChannelsSplit(2);
        draw->ChannelsSetCurrent(1);
        KennyIdentity::Draw(draw,origin,l.padding,l.brand,brandHeight,l.scale);

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
                               ImVec2(tabWidth, l.navHeight - 12.0f * l.scale))) {
                const bool changed=static_cast<int>(state.category)!=i;
                state.Select(static_cast<Category>(i), tab);
                if(changed)KennyAudio::Emit(KennyAudio::Event::PrimaryNavigation,i==4?"Settings":i==2&&tab==5?"Extra features":nullptr);
            }
        }
        // One bounded, time-based underline; no per-tab animation allocations.
        const float target = static_cast<float>(static_cast<int>(state.category));
        if (state.indicator < 0.0f || resumed) state.indicator = target;
        state.indicator = state.appearance.reducedMotion ? target :
            KennyMotion::Step(state.indicator, target, 18.0f, ImGui::GetIO().DeltaTime);
        const float underlineWidth = std::min(78.0f * l.scale, tabWidth * 0.65f);
        const float underlineX = origin.x + navX + (state.indicator + 0.5f) * tabWidth - underlineWidth * 0.5f;
        KennyPaint::Seam(draw,ImVec2(underlineX,origin.y+l.header-8*l.scale),underlineWidth,
                          Claude::Hex(0xEDA9B6,0.78f),std::max(1.0f,2*l.scale));
        KennyPaint::Seam(draw,ImVec2(origin.x+l.padding,origin.y+l.header),l.size.x-2*l.padding,
                          Claude::Hex(0x99818B,0.20f));

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
            const bool presentation = state.category == Category::Style || state.category == Category::Settings;
            if (Claude::PillTab(secondary[i], presentation || tab == values[i], ImVec2(widths[i], pillHeight)) && !presentation) {
                const bool changed=tab!=values[i];
                tab = values[i];
                if(changed)KennyAudio::Emit(KennyAudio::Event::SecondaryNavigation,secondary[i]);
                if (state.category == Category::Visual) state.visualTab = tab;
                if (state.category == Category::Misc) state.miscTab = tab;
            }
            x += widths[i] + gap;
        }
        const float contentY = l.header + l.secondary;
        KennyPaint::Seam(draw,ImVec2(origin.x+l.padding,origin.y+contentY),l.size.x-2*l.padding,
                          Claude::Hex(0x99818B,0.16f));

        // Isolate content scrolling from both navigation rows. No nested card border.
        ImGui::SetCursorPos(ImVec2(l.padding, contentY + 18.0f * l.scale));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        // The shared atmosphere already separates the content surface. A
        // second rectangular wash would create a hard strip below the child.
        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0,0,0,0));
        const bool interactiveBackground = state.appearance.theme == KennyAppearance::Theme::Aurora;
        ImGuiWindow* contentWindow = nullptr;
        if (ImGui::BeginChild("##content", ImVec2(l.size.x - 2.0f * l.padding,
                             l.size.y - contentY - 36.0f * l.scale), false,
                             (interactiveBackground ? ImGuiWindowFlags_NoMove : ImGuiWindowFlags_None) |
                             (acceptInput ? ImGuiWindowFlags_None : ImGuiWindowFlags_NoInputs))) {
            contentWindow = ImGui::GetCurrentWindow();
            // This ImGui version multiplies a child's scale by its parent's.
            ImGui::SetWindowFontScale(0.875f);
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing,
                                ImVec2(8.0f * l.scale, (state.appearance.compactRows ? 6.0f : 10.0f) * l.scale));
            ImGui::PushItemWidth(std::min(420.0f * l.scale, ImGui::GetContentRegionAvail().x * 0.58f));
            if (state.category == Category::Style) {
                KennyAppearance::DrawStyle(state.appearance,state.artwork.current.Valid()||(state.appearance.animeVideo&&state.animeVideoFrame.Valid()),state.storage.status,state.characters.Selected(state.appearance).artworkTexture.Valid());
            } else if (state.category == Category::Settings) {
                KennyAppearance::DrawSettings(state.appearance, state.centerRequested,
                                              state.audio && state.audio->mixer,state.audioStatus,&state.characters,state.videoStatus);
            } else {
                renderPanel();
            }
            ImGui::PopItemWidth();
            ImGui::PopStyleVar();
        }
        ImGui::EndChild();
        ImGui::PopStyleColor();
        ImGui::PopStyleVar();
        draw->ChannelsSetCurrent(0);
        if (state.appearance.theme == KennyAppearance::Theme::Aurora) {
            const auto& io = ImGui::GetIO();
            const auto& context = *ImGui::GetCurrentContext();
            // Empty content receives native focus (its MoveId) without moving
            // the window. Header dragging is unchanged. Never steal a widget,
            // scrollbar, popup, disabled item or a gesture begun elsewhere.
            const bool allowed = contentWindow && context.HoveredWindow == contentWindow &&
                contentWindow->InnerRect.Contains(io.MousePos) && context.HoveredId == 0 &&
                !context.HoveredIdDisabled &&
                (context.ActiveId == 0 || (state.aurora.gesture && context.ActiveId == contentWindow->MoveId)) &&
                state.appearance.touchAttraction && !state.appearance.reducedMotion && opened && acceptInput;
            if (io.MouseClicked[0]) state.aurora.gesture = allowed && context.ActiveId == 0;
            if (!io.MouseDown[0] || !allowed) state.aurora.gesture = false;
            const ImVec2 pointer((io.MousePos.x-origin.x)/l.size.x,(io.MousePos.y-origin.y)/l.size.y);
            state.aurora.Advance(ImGui::GetFrameCount(),io.DeltaTime,l.size,
                                 state.aurora.gesture,pointer,state.appearance.reducedMotion,
                                 state.appearance.particleActivity*.01f,state.appearance.starsVisible);
            KennyAurora::Draw(draw,origin,ImGui::GetWindowSize(),l.scale,Claude::RadiusWindow*l.scale,
                              state.aurora,state.appearance.reducedMotion,l.header,contentY,
                              state.appearance.auroraIntensity*.01f,state.appearance.starsVisible);
        } else {
            state.aurora.gesture = false;
            KennyThemeBackground::Surface(draw,origin,l.size,Claude::RadiusWindow*l.scale,l.header,contentY);
            if(state.appearance.theme == KennyAppearance::Theme::Classic) {
                state.electric.Advance(ImGui::GetFrameCount(),ImGui::GetIO().DeltaTime,state.appearance);
                KennyElectric::Draw(draw,origin,l.size,l.scale,Claude::RadiusWindow*l.scale,
                                    state.electric,state.appearance,l.header,contentY);
            }
            if(state.appearance.theme == KennyAppearance::Theme::Anime) {
                state.characters.Prepare(state.appearance,state.audio);
                state.artwork.Advance(ImGui::GetFrameCount(),ImGui::GetIO().DeltaTime,state.appearance.reducedMotion);
                auto& character=state.characters.Selected(state.appearance);
                if(state.appearance.animeVideo && state.animeVideoFrame.Valid())
                    KennyThemeBackground::DrawArtwork(draw,origin,l.size,Claude::RadiusWindow*l.scale,state.animeVideoFrame,state.appearance);
                else if(!character.artworkTexture.Valid())KennyThemeBackground::DrawArtwork(draw,origin,l.size,Claude::RadiusWindow*l.scale,state.artwork.current,state.appearance);
                if(character.artworkTexture.Valid())KennyCharacters::DrawCharacter(draw,origin,l.size,Claude::RadiusWindow*l.scale,contentY,character.artworkTexture,state.appearance);
            }
        }
        draw->ChannelsMerge();
        state.storage.Sync(state.appearance,!ImGui::IsAnyItemActive() || !opened);
        ImGui::EndDisabled();
    }
    ImGui::End();
    ImGui::PopStyleColor();
    ImGui::PopStyleVar(6);
    if (Font) ImGui::PopFont();
}

} // namespace KennyMenu
