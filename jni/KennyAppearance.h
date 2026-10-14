#pragma once
#include "KennyPanels.h"
#include "KennyThemePreferences.h"
#include "KennyCharacters.h"

// All controls are presentation-only; feature bindings stay in main.cpp.
namespace KennyAppearance {
inline void ThemeCard(Preferences& p, Theme theme, const char* description) {
    const float width=ImGui::GetContentRegionAvail().x;
    const float scale=KennyControls::Scale();
    const float height=std::max(96.0f,132.0f*scale);
    const ImVec2 start=ImGui::GetCursorScreenPos();
    for(ImGuiCol c:{ImGuiCol_Button,ImGuiCol_ButtonHovered,ImGuiCol_ButtonActive,ImGuiCol_Text})
        ImGui::PushStyleColor(c,ImVec4(0,0,0,0));
    if(ImGui::Button(ThemeName(theme),ImVec2(width,height)) && p.theme!=theme) {
        p.theme=theme;KennyAudio::Emit(KennyAudio::Event::ThemeChanged);
    }
    ImGui::PopStyleColor(4);
    const float emphasis=KennyMotion::Sample(ImGui::GetItemID(),0,p.theme==theme ? 1.0f : 0.0f);
    const float hover=KennyMotion::Sample(ImGui::GetItemID(),1,ImGui::IsItemHovered() ? 1.0f : 0.0f);
    auto* draw=ImGui::GetWindowDrawList();
    draw->AddRectFilled(start,ImVec2(start.x+width,start.y+height),
        ImGui::GetColorU32(KennyMotion::Mix(Claude::Hex(0x191217,.78f),
                          Claude::Hex(0x470D19,.78f),emphasis*.65f+hover*.1f)),14*scale);
    draw->AddRect(start,ImVec2(start.x+width,start.y+height),
        ImGui::GetColorU32(KennyMotion::Mix(Claude::Hex(0x665059,.35f),
                          Claude::Hex(0xEA8796,.62f),emphasis)),14*scale);
    const float pad=std::max(10.0f,16*scale);
    // Quiet typographic cards: no substitute anime artwork or custom logo.
    draw->AddText(ImVec2(start.x+pad,start.y+pad),
                  ImGui::GetColorU32(p.theme==theme ? Claude::Hex(0xF4C8D0) : Claude::Dark::textPrimary),ThemeName(theme));
    const float textWidth=std::max(1.0f,width-2*pad);
    draw->AddText(ImGui::GetFont(),ImGui::GetFontSize()*.72f,
                  ImVec2(start.x+pad,start.y+pad+ImGui::GetFontSize()+10*scale),
                  ImGui::GetColorU32(Claude::Dark::textSecondary),description,nullptr,textWidth);
    KennyPaint::Seam(draw,ImVec2(start.x+pad,start.y+height-10*scale),width-2*pad,
                    Claude::Hex(0xEA8796,.12f+.45f*emphasis),1);
    ImGui::RenderNavHighlight(ImRect(start,ImVec2(start.x+width,start.y+height)),ImGui::GetItemID());
}
inline void DrawStyle(Preferences& p, bool artworkReady=false, const char* storageStatus=nullptr, bool characterReady=false) {
    if(KennyPanels::Begin("##themes",3,4.0f)) {
        ImGui::TableNextColumn();ThemeCard(p,Theme::Aurora,"Living crimson light");
        ImGui::TableNextColumn();ThemeCard(p,Theme::Anime,"Your artwork, your atmosphere");
        ImGui::TableNextColumn();ThemeCard(p,Theme::Classic,"Crimson Eclipse / Electric Starfield");
        KennyPanels::End();
    }
    if(KennyPanels::Begin("##appearance",3,12.0f)) {
        KennyPanels::Section("Surface");
        KennyControls::SliderFloat("Menu opacity",&p.opacity,85.0f,100.0f,"%.0f%%");
        KennyPanels::Note("Text and controls keep their contrast.");KennyPanels::EndSection();
        KennyPanels::Section("Layout");
        KennyControls::Choice("Row spacing",&p.compactRows,"Standard","Compact");
        KennyPanels::Note("Applied immediately to every panel.");KennyPanels::EndSection();
        KennyPanels::Section("Motion");
        KennyControls::Choice("Atmosphere",&p.reducedMotion,"Full","Reduced");
        KennyPanels::Note("Reduced holds the background and makes transitions immediate.");KennyPanels::EndSection();
        KennyPanels::End();
    }
    if(p.theme==Theme::Aurora && KennyPanels::Begin("##aurora-settings",2,12.0f,"Touch attraction")) {
        KennyPanels::Section("Aurora light");
        KennyControls::SliderFloat("Aurora intensity",&p.auroraIntensity,0,100,"%.0f%%");
        KennyControls::SliderFloat("Particle activity",&p.particleActivity,0,100,"%.0f%%");
        KennyPanels::Note("Zero activity holds stars in place; the curtains keep flowing.");KennyPanels::EndSection();
        KennyPanels::Section("Starfield interaction");
        KennyControls::Checkbox("Show stars",&p.starsVisible);
        KennyControls::Checkbox("Touch attraction",&p.touchAttraction);
        KennyPanels::Note("Only empty content reacts. Controls and the drag header keep priority.");KennyPanels::EndSection();
        KennyPanels::End();
    } else if(p.theme==Theme::Anime) {
        if((artworkReady||characterReady) && KennyPanels::Begin("##artwork",2,12.0f)) {
            KennyPanels::Section("Artwork surface");
            KennyControls::SliderFloat("Artwork dimming",&p.artworkDim,35,95,"%.0f%%");KennyPanels::EndSection();
            KennyPanels::Section("Composition");
            if(characterReady)KennyPanels::Note("Character cutouts keep their full silhouette and original aspect ratio.");
            else KennyControls::Choice("Artwork fit",&p.artworkCover,"Contain","Cover");
            KennyPanels::EndSection();
            KennyPanels::End();
        } else KennyPanels::Note("Anime is selected. No artwork is installed yet; a quiet dark surface keeps every control usable. Your artwork will appear here when installed.");
    } else if(p.theme==Theme::Classic) {
        KennyPanels::Note("Classic uses static black and crimson surfaces. Animated backgrounds stay off.");
    }
    Normalize(p);
    if(storageStatus) KennyPanels::Note(storageStatus);
}

inline void DrawAnime(Preferences& p,KennyCharacters::Registry& registry,bool audioReady){
    if(p.theme!=Theme::Anime)return;
    auto& character=registry.Selected(p);
    const ImVec2 padding=ImGui::GetStyle().FramePadding;
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding,ImVec2(padding.x,std::max(padding.y,(36.0f-ImGui::GetFontSize())*.5f)));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding,Claude::RadiusInput);
    if(!KennyPanels::Begin("##anime-character",2,12.0f,"Character launcher")){ImGui::PopStyleVar(2);return;}
    KennyPanels::Section("Anime character");
    ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
    if(ImGui::BeginCombo("##anime-character-id",character.name.c_str())){
        for(unsigned i=0;i<registry.count;++i){auto& c=registry.characters[i];
            ImGui::PushID(c.id.c_str());if(ImGui::Selectable(c.name.c_str(),p.characterId==c.id)){p.characterId=c.id;KennyAudio::Emit(KennyAudio::Event::ButtonPressed);}ImGui::PopID();}
        ImGui::EndCombo();
    }
    KennyPanels::Note(character.series.c_str());KennyPanels::Note(character.status.c_str());
    KennyPanels::Note(character.artworkTexture.Valid()?"Transparent artwork ready.":character.image.rgba.empty()?"Character artwork missing or invalid.":"Artwork decoded; texture rendering unavailable.");
    KennyControls::Checkbox("Show character artwork",&p.artworkVisible);
    ImGui::BeginDisabled(!character.launcherTexture.Valid());KennyControls::Checkbox("Character launcher",&p.characterLauncher);ImGui::EndDisabled();
    KennyPanels::Note(character.launcherTexture.Valid()?"Character launcher ready.":"Launcher artwork unavailable; using the K emblem.");KennyPanels::EndSection();
    KennyPanels::Section("Character voice");
    auto* pack=registry.Pack(character,p.voicePack);bool available=pack&&pack->Available();
    if(character.packCount){ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
        if(ImGui::BeginCombo("##voice-pack",pack?pack->name.c_str():"Select installed pack")){
            for(unsigned i=0;i<character.packCount;++i){auto& v=character.packs[i];ImGui::PushID(v.id.c_str());if(ImGui::Selectable(v.name.c_str(),p.voicePack==v.id)){p.voicePack=v.id;KennyAudio::Emit(KennyAudio::Event::ButtonPressed);}ImGui::PopID();}ImGui::EndCombo();}}
    ImGui::BeginDisabled(!audioReady||!available);
    KennyControls::Checkbox("Character voice",&p.characterVoice);
    KennyControls::Checkbox("Control voice feedback",&p.controlVoiceFeedback);
    KennyControls::SliderFloat("Voice volume",&p.characterVolume,0,100,"%.0f%%");ImGui::EndDisabled();
    KennyPanels::Note(!available?"Voice recordings unavailable. UI tones remain the fallback.":!audioReady?"Voice pack decoded; Android playback unavailable on this host.":"Local voice pack ready. Global UI mute takes precedence.");
    if(available){unsigned events=0;for(const auto& e:pack->events)events+=e.count>0;ImGui::Text("Mapped events: %u / %u",events,KennyCharacters::EventCount);}
    KennyPanels::Note(registry.mediaStatus);
    // Diagnostic action stays available with missing assets/engine so failure is
    // explained, and deliberately emits no generic button tone or feature edit.
    if(pack){
        if(!pack->events[unsigned(registry.testEvent)].count&&!pack->mappingDefined[unsigned(registry.testEvent)]){
            for(unsigned e=0;e<KennyCharacters::EventCount;++e)if(pack->events[e].count){registry.testEvent=static_cast<KennyCharacters::VoiceEvent>(e);break;}
        }
        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
        if(ImGui::BeginCombo("##voice-test-event",KennyCharacters::EventNames[unsigned(registry.testEvent)])){
            for(unsigned e=0;e<KennyCharacters::EventCount;++e)if(pack->events[e].count||pack->mappingDefined[e]){
                if(ImGui::Selectable(KennyCharacters::EventNames[e],unsigned(registry.testEvent)==e))registry.testEvent=static_cast<KennyCharacters::VoiceEvent>(e);
            }ImGui::EndCombo();}}
    if(KennyControls::Button("Test Voice",false))registry.TestVoice(p,audioReady?KennyAudio::current.dispatcher:nullptr,ImGui::GetTime());
    KennyPanels::Note(KennyAudioDiagnostics::Status(registry.testResult));
    if(registry.testAttempted&&registry.testResult==KennyAudioDiagnostics::Result::Queued){
        auto* dispatcher=KennyAudio::current.dispatcher;auto* mix=dispatcher?dispatcher->mixer:nullptr;
        if(!mix)KennyPanels::Note("Audio engine became unavailable; see playback diagnostics.");
        else if(!mix->transport.native.load())KennyPanels::Note("Host PCM test sink only; Android speakers unverified.");
        else if(mix->transport.recordingsStarted.load()>registry.testStartedBefore&&mix->transport.callbacks.load()>registry.testCallbacksBefore)KennyPanels::Note("Recording mixed and OpenSL consumed a subsequent buffer. Verify speakers.");
        else KennyPanels::Note("Waiting for an OpenSL callback; check playback diagnostics.");
    }
    KennyPanels::EndSection();KennyPanels::End();ImGui::PopStyleVar(2);
}
inline void DrawSettings(Preferences& preferences, bool& centerRequested, bool audioReady=false,
                         const char* audioStatus="UI audio unavailable in this host preview.", KennyCharacters::Registry* characters=nullptr) {
    if (!KennyPanels::Begin("##general", 2, 12.0f)) return;
    KennyPanels::Section("Menu");
    if (KennyControls::Button("Center window")) centerRequested = true;
    if (KennyControls::Button("Reset appearance")) preferences = Preferences{};
    KennyPanels::Note("Restore Aurora and all default appearance preferences.");
    KennyPanels::EndSection();
    KennyPanels::Section("About");
    ImGui::TextUnformatted("KennyPvtHax");
    KennyPanels::Note("Crimson Eclipse");
    KennyPanels::Note("Android landscape interface");
    KennyPanels::EndSection();
    KennyPanels::End();
    if(KennyPanels::Begin("##ui-audio",2,12.0f,"UI sounds")) {
        KennyPanels::Section("Interface audio");
        ImGui::BeginDisabled(!audioReady);
        KennyControls::Checkbox("UI sounds",&preferences.uiSounds);
        KennyControls::SliderFloat("UI sound volume",&preferences.uiVolume,0,100,"%.0f%%");
        ImGui::EndDisabled();
        KennyPanels::Note(audioStatus);KennyPanels::EndSection();
        KennyPanels::Section("Sound character");
        ImGui::BeginDisabled(!audioReady);
        const ImVec2 audioPadding=ImGui::GetStyle().FramePadding;
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding,ImVec2(audioPadding.x,
            std::max(audioPadding.y,(36.0f-ImGui::GetFontSize())*.5f)));
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding,Claude::RadiusInput);
        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
        if(ImGui::Combo("##sound-profile",&preferences.soundProfile,"Follow theme\0Aurora / soft\0Classic / crisp\0"))
            KennyAudio::Emit(KennyAudio::Event::ButtonPressed);
        ImGui::PopStyleVar(2);
        ImGui::EndDisabled();
        KennyPanels::Note("Follow theme uses soft Aurora tones or crisp Classic feedback. Anime uses the selected installed voice pack.");
        KennyPanels::EndSection();KennyPanels::End();
    }
    if(preferences.theme==Theme::Classic && KennyPanels::Begin("##classic-effects",2,12.0f,"Lightning intensity")) {
        KennyPanels::Section("Classic Background Effects");
        KennyControls::Checkbox("Enable Electric Starfield",&preferences.electricStarfield);
        const auto padding=ImGui::GetStyle().FramePadding;
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding,ImVec2(padding.x,std::max(padding.y,(36.0f-ImGui::GetFontSize())*.5f)));
        ImGui::TextUnformatted("Star Density");
        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
        ImGui::Combo("##electric-density",&preferences.electricDensity,"Low\0Medium\0High\0");
        ImGui::PopStyleVar();
        KennyControls::Checkbox("Energy Pulses",&preferences.electricPulses);
        KennyControls::Checkbox("Reduced Motion",&preferences.electricReducedMotion);
        KennyPanels::Note("Reduced holds stars and filaments; traveling pulses stop.");KennyPanels::EndSection();
        KennyPanels::Section("Electric atmosphere");
        KennyControls::SliderFloat("Lightning intensity",&preferences.electricLightning,0,100,"%.0f%%");
        KennyControls::SliderFloat("Sparkle intensity",&preferences.electricSparkle,0,100,"%.0f%%");
        KennyControls::SliderFloat("Animation speed",&preferences.electricSpeed,0,100,"%.0f%%");
        KennyPanels::Note("Classic only. Global Reduced motion also holds this background.");KennyPanels::EndSection();KennyPanels::End();
    }
    if(characters)DrawAnime(preferences,*characters,audioReady);
    Normalize(preferences);
}

} // namespace KennyAppearance
