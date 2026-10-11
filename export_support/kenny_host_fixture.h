#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include "KennyMenu.h"
#include "KennyPanels.h"
#include "imgui/imgui_internal.h"
#include "ANOY/CustomFont.h"
#include "ANOY/fontAwesome.hpp"
enum EAimTrigger {
    None = 0,
    Shooting = 1,
    Scoping = 2,
    Both = 3,
    Any = 4
};

enum EAimTarget
{
    Head = 0,
    Chest = 1
};

namespace Cheat {
    namespace Esp 
    {
        bool Line = false;
        bool Skeleton = false;
        bool Health = false;
        bool Distance = false;
        bool Name = false;
        bool Box = false;
        bool LootBox = false;
        bool Throwable = false;
        bool Counter = false;
        bool Target = false;
        bool ItemEsp = false;
        bool Aiming = false;
        bool WeaponName = false;   // ← add this
        bool Alert = false;   // ← add this

        namespace Vehicle 
        {
            bool Name = true;
            bool Health = false;
            bool Fuel = false;
        }
    }

        namespace BulletTrack {
bool Enable;
bool Enablev2;
bool VisCheck;
bool IgnoreKnock;
bool IgnoreBot;
bool AutoFire;
bool AutoFireOff = false;
float Range = 0;
float AimSet = 0.0f;
auto AimPrediction = 0;
float Radius = 300.0f;
int BulletCounter = 0;
bool ForceHeadshotWhenFull;
int TrackingAccuracy; // 1 = 1/3, 2 = 2/3, 3 = 3/3
}

// Silent view color (RGB 0-1)
float SilentViewColor[4] = { 0.00f, 1.00f, 1.00f, 1.0f };

namespace Aimbot {
bool Enable;
bool VisCheck;
bool IgnoreKnock;
bool IgnoreBot;
bool AimPrediction;
EAimTrigger Trigger;
EAimTarget Target;
float RecoilControl;
float RecoilSet = 1.050f;
float Range = 150.0f;
float Radius = 300.0f;
float Smoothing = 4.0;
float FireSpeed;
bool EnableFov = false;
bool ShowFovCircle = true;   // ← new: hide

}


    namespace Memory 
    {
        bool Wide = false;
        bool Hit = false;
        bool Small = false;
        bool Skin = false;
        bool Magic = false;
		bool ShowDamage = false;
		bool IPad = false;  
		bool IslandBp = false;
        
        float Size = 10000.0f;
    }
}
namespace Settings { int Tab = 1; }
void ResetLogin() { std::abort(); }
struct Control { ImGuiID id; ImVec2 min, max; };
std::map<std::pair<int,std::string>,Control> controls;
std::set<std::pair<int,std::string>> rendered;
void RecordBefore(const char* label) { controls[{Settings::Tab,label}].id=ImGui::GetID(label); }
void RecordAfter(const char* label) {
 auto& c=controls[{Settings::Tab,label}];c.min=ImGui::GetItemRectMin();c.max=ImGui::GetItemRectMax();
 rendered.insert({Settings::Tab,label});
 const std::string name(label);
 if(name.rfind("Aim ",0)==0 || name=="Recoil compensation" || name=="Tracking accuracy")
  assert(ImGui::CalcTextSize(label).x<=c.max.x-c.min.x+1);
 auto* table=ImGui::GetCurrentTable();
 if(table && c.max.x > table->Columns[table->CurrentColumn].WorkMaxX+1) {
  std::fprintf(stderr,"CLIPPED control: tab=%d label=%s x=%.1f bound=%.1f\n", Settings::Tab,label,c.max.x,table->Columns[table->CurrentColumn].WorkMaxX);
  std::abort();
 }
}
void Panels() {
            if (Settings::Tab == 1) {
                if (KennyPanels::Begin("##players", 3)) {
                    KennyPanels::Section("Player");
                    RecordBefore("ESP line"); KennyControls::Checkbox("ESP line",     &Cheat::Esp::Line); RecordAfter("ESP line");
                    RecordBefore("ESP skeleton"); KennyControls::Checkbox("ESP skeleton", &Cheat::Esp::Skeleton); RecordAfter("ESP skeleton");
                    RecordBefore("ESP health"); KennyControls::Checkbox("ESP health",   &Cheat::Esp::Health); RecordAfter("ESP health");
                    RecordBefore("ESP box"); KennyControls::Checkbox("ESP box",      &Cheat::Esp::Box); RecordAfter("ESP box");
                    KennyPanels::EndSection();
                    KennyPanels::Section("Labels");
                    RecordBefore("ESP name"); KennyControls::Checkbox("ESP name",     &Cheat::Esp::Name); RecordAfter("ESP name");
                    RecordBefore("ESP distance"); KennyControls::Checkbox("ESP distance", &Cheat::Esp::Distance); RecordAfter("ESP distance");
                    RecordBefore("Counter"); KennyControls::Checkbox("Counter",      &Cheat::Esp::Counter); RecordAfter("Counter");
                    KennyPanels::EndSection();
                    KennyPanels::Section("World");
                    RecordBefore("Alert"); KennyControls::Checkbox("Alert",        &Cheat::Esp::Alert); RecordAfter("Alert");
                    RecordBefore("Loot box"); KennyControls::Checkbox("Loot box",     &Cheat::Esp::LootBox); RecordAfter("Loot box");
                    RecordBefore("Vehicle name"); KennyControls::Checkbox("Vehicle name", &Cheat::Esp::Vehicle::Name); RecordAfter("Vehicle name");
                    KennyPanels::EndSection();
                    KennyPanels::End();
                }
            }
            else if (Settings::Tab == 2) {
                if (KennyPanels::Begin("##world", 2, 12.0f)) {
                    KennyPanels::Section("Threats & targeting");
                    RecordBefore("Throwable"); KennyControls::Checkbox("Throwable",    &Cheat::Esp::Throwable); RecordAfter("Throwable");
                    RecordBefore("Target line"); KennyControls::Checkbox("Target line",  &Cheat::Esp::Target); RecordAfter("Target line");
                    KennyPanels::EndSection();
                    KennyPanels::Section("Equipment");
                    RecordBefore("Enemy weapon"); KennyControls::Checkbox("Enemy weapon", &Cheat::Esp::WeaponName); RecordAfter("Enemy weapon");
                    KennyPanels::EndSection();
                    KennyPanels::End();
                }
            }
            else if (Settings::Tab == 3) {
                if (KennyPanels::Begin("##aim", 2, 12.0f)) {
                    KennyPanels::Section("Targeting");
                    RecordBefore("Enable aimbot"); KennyControls::Checkbox("Enable aimbot", &Cheat::Aimbot::Enable); RecordAfter("Enable aimbot");
                    RecordBefore("Aim range"); KennyControls::SliderFloat("Aim range", &Cheat::Aimbot::Range, 0.0f, 400.0f, "%.0f m"); RecordAfter("Aim range");
                    KennyPanels::EndSection();
                    KennyPanels::Section("Filtering");
                    RecordBefore("Visibility check"); KennyControls::Checkbox("Visibility check", &Cheat::Aimbot::VisCheck); RecordAfter("Visibility check");
                    RecordBefore("Ignore knocked"); KennyControls::Checkbox("Ignore knocked", &Cheat::Aimbot::IgnoreKnock); RecordAfter("Ignore knocked");
                    RecordBefore("Ignore bot"); KennyControls::Checkbox("Ignore bot", &Cheat::Aimbot::IgnoreBot); RecordAfter("Ignore bot");
                    KennyPanels::EndSection();
                    KennyPanels::Section("Tuning");
                    RecordBefore("Aim smoothing"); KennyControls::SliderFloat("Aim smoothing", &Cheat::Aimbot::Smoothing, 1.0f, 4.0f, "%.0f"); RecordAfter("Aim smoothing");
                    RecordBefore("Recoil compensation"); KennyControls::SliderFloat("Recoil compensation", &Cheat::Aimbot::RecoilSet, 0.0f, 2.0f); RecordAfter("Recoil compensation");
                    KennyPanels::EndSection();
                    KennyPanels::Section("Field of view");
                    RecordBefore("Enable FOV"); KennyControls::Checkbox("Enable FOV", &Cheat::Aimbot::EnableFov); RecordAfter("Enable FOV");
                    if (Cheat::Aimbot::EnableFov) {
                        RecordBefore("Aim FOV"); KennyControls::SliderFloat("Aim FOV", &Cheat::Aimbot::Radius, 0.0f, 400.0f, "%.0f"); RecordAfter("Aim FOV");
                        RecordBefore("Show FOV circle"); KennyControls::Checkbox("Show FOV circle", &Cheat::Aimbot::ShowFovCircle); RecordAfter("Show FOV circle");
                    }
                    KennyPanels::EndSection();
                    KennyPanels::End();
                }
            }
            else if (Settings::Tab == 4) {
                if (KennyPanels::Begin("##tracking", 3, 10.0f, "Force headshot on full")) {
                    KennyPanels::Section("Tracking");
                    RecordBefore("Enable bullet track"); KennyControls::Checkbox("Enable bullet track", &Cheat::BulletTrack::Enable); RecordAfter("Enable bullet track");
                    RecordBefore("Force headshot on full"); KennyControls::Checkbox("Force headshot on full", &Cheat::BulletTrack::ForceHeadshotWhenFull); RecordAfter("Force headshot on full");
                    RecordBefore("Tracking accuracy"); KennyControls::SliderInt("Tracking accuracy", &Cheat::BulletTrack::TrackingAccuracy, 1, 3, "%d/3"); RecordAfter("Tracking accuracy");
                    KennyPanels::EndSection();
                    KennyPanels::Section("Filtering");
                    RecordBefore("Visibility check"); KennyControls::Checkbox("Visibility check", &Cheat::Aimbot::VisCheck); RecordAfter("Visibility check");
                    RecordBefore("Ignore knocked"); KennyControls::Checkbox("Ignore knocked", &Cheat::Aimbot::IgnoreKnock); RecordAfter("Ignore knocked");
                    RecordBefore("Ignore bot"); KennyControls::Checkbox("Ignore bot", &Cheat::Aimbot::IgnoreBot); RecordAfter("Ignore bot");
                    KennyPanels::EndSection();
                    KennyPanels::Section("Field of view");
                    RecordBefore("Enable FOV"); KennyControls::Checkbox("Enable FOV", &Cheat::Aimbot::EnableFov); RecordAfter("Enable FOV");
                    if (Cheat::Aimbot::EnableFov) {
                        RecordBefore("Aim FOV"); KennyControls::SliderFloat("Aim FOV", &Cheat::Aimbot::Radius, 0.0f, 400.0f, "%.0f"); RecordAfter("Aim FOV");
                        RecordBefore("Show FOV circle"); KennyControls::Checkbox("Show FOV circle", &Cheat::Aimbot::ShowFovCircle); RecordAfter("Show FOV circle");
                    }
                    RecordBefore("Aim range"); KennyControls::SliderFloat("Aim range", &Cheat::Aimbot::Range, 0.0f, 400.0f, "%.0f m"); RecordAfter("Aim range");
                    KennyPanels::EndSection();
                    KennyPanels::End();
                }
            }
            else if (Settings::Tab == 5) {
                if (KennyPanels::Begin("##extras", 2, 12.0f)) {
                    KennyPanels::Section("Presentation");
                    RecordBefore("Small cross"); KennyControls::Checkbox("Small cross", &Cheat::Memory::Small); RecordAfter("Small cross");
                    RecordBefore("X-hit effect"); KennyControls::Checkbox("X-hit effect", &Cheat::Memory::Hit); RecordAfter("X-hit effect");
                    RecordBefore("iPad view"); KennyControls::Checkbox("iPad view", &Cheat::Memory::IPad); RecordAfter("iPad view");
                    KennyPanels::EndSection();
                    KennyPanels::Section("Utilities");
                    RecordBefore("6-hour fixer"); KennyControls::Checkbox("6-hour fixer", &Cheat::Memory::IslandBp); RecordAfter("6-hour fixer");
                    if (KennyControls::Button("Guest Reset")) {
                        ResetLogin();
                    }
                    KennyPanels::EndSection();
                    KennyPanels::End();
                }
            }
}
