#include "KennyDiagnostics.h"
#include "KennyStartup.h"
#include <atomic>
#include "Helper/include.h"
#include "Helper/definition.h"
#include "Helper/Items.h"
#include "Helper/Login.h"
#include "Helper/bypass.h"
#include "Helper/Hit.h"
#include <fcntl.h>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string>
// Keep presentation types ABI-compatible with separately compiled ImGui even
// when an earlier owner header leaves a narrower packing mode in effect.
// Restore that incoming mode before including the original native Lua source.
#pragma pack(push, 8)
#include "ClaudeTheme.h"
#include "KennyMenu.h"
#include "KennyLauncher.h"
#include "KennyAndroidAudio.h"
#include "KennyCharacterGL.h"
#include "KennyAndroidVideo.h"
#include "KennyPanels.h"
#pragma pack(pop)
#include "Lua_Buffer.cpp"


static std::atomic<bool> NativeGlobalsReady{false};
static std::atomic<android_app*> PresentationApp{nullptr};

// The Android host may call these through a JNI bridge/dlsym on a worker thread.
extern "C" __attribute__((visibility("default"))) bool KennyPvtHaxDiagnosticsSetStorage(const char* directory) {
    const bool ok=KennyDiagnostics::SetStorage(directory);
    KennyDiagnostics::Once(27,ok?KennyDiagnostics::Severity::Info:KennyDiagnostics::Severity::Warning,ok?0:errno,ok,"Host private-storage registration");
    return ok;
}
extern "C" __attribute__((visibility("default"))) bool KennyPvtHaxDiagnosticsExportToFd(int destination,unsigned previous) {
    return KennyDiagnostics::ExportToFd(destination,previous);
}

json items_data;
std::map<int, bool> Items;

void ResetLogin() {
system("rm -rf /data/data/com.pubg.imobile/shared_prefs");
system("rm -rf /data/data/com.pubg.imobile/files");
system("rm -rf /data/data/com.pubg.imobile/databases");
}

int _SDK() {
    char p[PROP_VALUE_MAX];
    __system_property_get(OBFUSCATE("ro.build.version.sdk"), p);
    return atoi(p);
}

static bool opened = true;
bool ShowMenu = true;

ImFont *font2 = nullptr;
ImFont *pRegularFont = nullptr;

ImVec4 to_vec4(float r, float g, float b, float a)
{
    return ImVec4(r / 255.0, g / 255.0, b / 255.0, a / 255.0);
}

static string compilation_date = __DATE__;
static string compilation_time = __TIME__;

int32_t (*orig_ANativeWindow_getHeight)(ANativeWindow *window);
int32_t _ANativeWindow_getHeight(ANativeWindow *window) {
    screenHeight = orig_ANativeWindow_getHeight(window);
    return orig_ANativeWindow_getHeight(window);
}

int32_t (*orig_ANativeWindow_getWidth)(ANativeWindow *window);
int32_t _ANativeWindow_getWidth(ANativeWindow *window) {
    screenWidth = orig_ANativeWindow_getWidth(window);
    return orig_ANativeWindow_getWidth(window);
}

void (*orig_onInputEvent)(void *thiz, void *ex_ab, void *ex_ac);
void _OI(void *thiz, void *ex_ab, void *ex_ac) {
    // These libinput hooks receive InputConsumer/MotionEvent C++ instances,
    // not AInputEvent handles. Preserve forwarding; never reinterpret thiz for UI.
    if(orig_onInputEvent)orig_onInputEvent(thiz, ex_ab, ex_ac);
}

int (*orig_AInputQueue_getEvent)(AInputQueue*, AInputEvent**);
int _HAI(AInputQueue* q, AInputEvent** e) {
    if(!orig_AInputQueue_getEvent)return -1;
    const int r=orig_AInputQueue_getEvent(q,e);
    if(r<0||!e||!*e)return r;
    const int type=AInputEvent_getType(*e);
    if(type==AINPUT_EVENT_TYPE_MOTION){
        const int raw=AMotionEvent_getAction(*e);
        const int action=raw&AMOTION_EVENT_ACTION_MASK;
        const size_t index=(raw&AMOTION_EVENT_ACTION_POINTER_INDEX_MASK)>>AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
        if(index>=AMotionEvent_getPointerCount(*e))return r;
        if(action==AMOTION_EVENT_ACTION_DOWN||action==AMOTION_EVENT_ACTION_POINTER_DOWN||
           action==AMOTION_EVENT_ACTION_UP||action==AMOTION_EVENT_ACTION_POINTER_UP||
           action==AMOTION_EVENT_ACTION_MOVE||action==AMOTION_EVENT_ACTION_CANCEL){
            KennyStartup::Input input;
            input.x=AMotionEvent_getX(*e,index);input.y=AMotionEvent_getY(*e,index);
            input.transition=action!=AMOTION_EVENT_ACTION_MOVE;
            input.down=action==AMOTION_EVENT_ACTION_DOWN||action==AMOTION_EVENT_ACTION_POINTER_DOWN;
            if(action==AMOTION_EVENT_ACTION_CANCEL)input.down=false;
            KennyStartup::Inputs().Push(input);
        }
    }else if(type==AINPUT_EVENT_TYPE_KEY){
        KennyStartup::Input input;input.kind=KennyStartup::Input::Key;
        input.code=AKeyEvent_getKeyCode(*e);input.modifiers=AKeyEvent_getMetaState(*e);input.down=AKeyEvent_getAction(*e)==AKEY_EVENT_ACTION_DOWN;
        if(input.code>=0&&input.code<512)KennyStartup::Inputs().Push(input);
    }
    return r; // Never consumes or filters the host application's input.
}



bool logged = false;
const char *Gamepackage = "com.pubg.imobile";





void ApplyIPadView()
{
    static ULocalPlayer* UlocalPlayer = nullptr;
    static EAspectRatioAxisConstraint OrigView = EAspectRatioAxisConstraint::AspectRatio_MaintainXFOV;
    static bool origCaptured = false;

    if (!UlocalPlayer)
    {
        UlocalPlayer = UObject::FindObject<ULocalPlayer>(
            "LocalPlayer Transient.UAEGameEngine_1.LocalPlayer_1");
    }
    if (!UlocalPlayer) return;

    // Capture the original value ONCE (shared for both on/off paths)
    if (!origCaptured)
    {
        OrigView = UlocalPlayer->AspectRatioAxisConstraint;
        origCaptured = true;
    }

    if (Cheat::Memory::IPad)
    {
        if (Cheat::localController != nullptr)
        {
            UlocalPlayer->AspectRatioAxisConstraint =
                EAspectRatioAxisConstraint::AspectRatio_MaintainYFOV;
        }
    }
    else
    {
        // Restore original view when toggled off
        if (UlocalPlayer->AspectRatioAxisConstraint != OrigView)
        {
            UlocalPlayer->AspectRatioAxisConstraint = OrigView;
        }
    }
}



void DrawHUD(AHUD* HUD)
{

ApplyIPadView();

    if (Cheat::localPlayer && Cheat::localController)
    {
        int totalEnemies = 0;
        int totalBots = 0;
        auto AllActors = GetActors();

        for (auto& i : AllActors)
        {
            auto Actor = i;

            if (isObjectInvalid(Actor))
                continue;

            if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass()))
            {
                auto Player = (ASTExtraPlayerCharacter*)Actor;
                bool IsVisible = Cheat::localController->LineOfSightTo(Player, { 0, 0, 0 }, true);

                FLinearColor White;
                FLinearColor boxColor;

                if (IsVisible)
                {
                    White = FLinearColor(0.0f, 1.0f, 0.0f, 1.0f);
                    boxColor = FLinearColor(1.0f, 1.0f, 1.0f, 0.7f);
                }
                else
                {
                    White = FLinearColor(1.0f, 0.0f, 0.0f, 1.0f);
                    boxColor = FLinearColor(1.0f, 0.0f, 0.0f, 0.7f);
                }

                float Distance = Cheat::localPlayer->GetDistanceTo(Player) / 100.0f;

                if (Player->PlayerKey == Cheat::localController->PlayerKey ||
                    Player->TeamID == Cheat::localController->TeamID ||
                    Player->bDead ||
                    Player->bHidden)
                    continue;

                if (Player->bEnsure)
                    totalBots++;
                else
                    totalEnemies++;

                auto HeadPos = Player->GetBonePos("Head", {});
                FVector2D headPosSC;
                auto RootPos = Player->GetBonePos("Root", {});
                FVector2D RootPosSC;

                if (W2S(HeadPos, &headPosSC) && W2S(RootPos, &RootPosSC))
                {
                    if (Cheat::Esp::Skeleton)
					{
    					static std::vector<std::vector<std::string>> skeleton =
    					{
        					{ "Head", "neck_01", "spine_03", "spine_02", "spine_01", "pelvis" },
        					{ "neck_01", "clavicle_r", "upperarm_r", "lowerarm_r", "hand_r", "item_r" },
        					{ "neck_01", "clavicle_l", "upperarm_l", "lowerarm_l", "hand_l", "item_l" },
        					{ "pelvis", "thigh_r", "calf_r", "foot_r" },
        					{ "pelvis", "thigh_l", "calf_l", "foot_l" }
    					};

    					for (auto& boneStructure : skeleton)
    					{
        					std::string lastBone;
        for (std::string& currentBone : boneStructure)
        {
            if (!lastBone.empty())
            {
                FVector2D boneFrom, boneTo;
                if (W2S(Player->GetBonePos(lastBone.c_str(), {}), &boneFrom) &&
                    W2S(Player->GetBonePos(currentBone.c_str(), {}), &boneTo))
                {
                    HUD->DrawLine(boneFrom.X, boneFrom.Y, boneTo.X, boneTo.Y, White, 1.5f);
                }
            }
            lastBone = currentBone;
        }
    }

    // Draw circle on head as before
    FVector head3D = Player->GetBonePos("Head", {});
    FVector2D headPos2D;
    if (W2S(head3D, &headPos2D))
    {
        FVector top3D = head3D;
        top3D.Z += 15.0f;
        FVector2D top2D;
        if (W2S(top3D, &top2D))
        {
            float radius = FVector2D::Distance(headPos2D, top2D);
            DrawCircleHelper(HUD, headPos2D.X, headPos2D.Y, radius, White, 36, 1.5f);
        }
    }
}

                    float height = fabs(RootPosSC.Y - headPosSC.Y);
                    float extraTop = height * 0.10f;
                    float totalHeight = height + extraTop;
                    float width = totalHeight / 2.0f;
                    float x = headPosSC.X - width / 2.0f;
                    float y = headPosSC.Y - extraTop;

                    if (Cheat::Esp::Box)
                    {
                        Box4LineHUD(HUD, x, y, width, totalHeight, 1.2f, 0.25f / 2.0f, boxColor);
                    }

                    if (Cheat::Esp::Health)
                    {
                        float CurHP = std::max(0.f, std::min(Player->Health, Player->HealthMax));
                        float MaxHP = Player->HealthMax;
                        float KnockHealth = Player->NearDeathBreath;
                        float HealthPercentage = CurHP / MaxHP;

                        FLinearColor HPColor;
                        if (CurHP > 70.0f)
                            HPColor = FLinearColor(0.0f, 0.7f, 0.8f, 1.0f);
                        else if (CurHP > 30.0f)
                            HPColor = FLinearColor(1.0f, 1.0f, 0.0f, 1.0f);
                        else if (CurHP > 0.0f)
                            HPColor = FLinearColor(1.0f, 0.0f, 0.0f, 1.0f);
                        else
                        {
                            HPColor = FLinearColor(0.5f, 0.0f, 0.0f, 1.0f);
                            HealthPercentage = KnockHealth / MaxHP;
                        }

                        float BarHeight = totalHeight;
                        float BarWidth = 3.0f;
                        float spacing = width * 0.1f;

                        float BarX = x - BarWidth - spacing;
                        float BarY = y;

                        DrawFilledRectangle(HUD, FVector2D(BarX, BarY), BarWidth, BarHeight, FLinearColor(0.f, 0.f, 0.f, 0.5f));

                        float FilledHeight = BarHeight * HealthPercentage;
                        float FilledY = BarY + (BarHeight - FilledHeight);
                        DrawFilledRectangle(HUD, FVector2D(BarX, FilledY), BarWidth, FilledHeight, HPColor);
                    }

                    if (Cheat::Esp::Line)
                    {
                        float lineStartX = (float)glWidth / 2;
                        float lineStartY = 0.0f;
                        float lineEndX = headPosSC.X;
                        float lineEndY = y - 5.0f;
                        HUD->DrawLine(lineStartX, lineStartY, lineEndX, lineEndY, White, 1.5f);
                    }
                    
                    
                    if (Cheat::Esp::WeaponName)
{
    std::string weaponname = "Fist";

    if (auto WeaponManagerComponent = Player->WeaponManagerComponent)
    {
        auto PropSlot = WeaponManagerComponent->GetCurrentUsingPropSlot();
        if ((int)PropSlot.GetValue() >= 1 && (int)PropSlot.GetValue() <= 3)
        {
            if (auto CurrentWeaponReplicated = WeaponManagerComponent->CurrentWeaponReplicated)
            {
                weaponname = CurrentWeaponReplicated->GetWeaponName().ToString();
            }
        }
    }

    // Colors: bot → cyan-ish, real player → yellow (same as your original)
    FLinearColor weaponColor = Player->bEnsure
        ? FLinearColor(0.0f, 1.0f, 240.f / 255.f, 1.0f)   // IM_COL32(0, 255, 240, 255)
        : FLinearColor(1.0f, 240.f / 255.f, 0.0f, 1.0f);  // IM_COL32(255, 240, 0, 255)

    // DrawOutlinedText centers horizontally on the X you pass (isCenter = true),
    // so we don't need CalcTextSize / manual offset anymore.
    FVector2D weaponPos = { headPosSC.X, headPosSC.Y - 29.5f };

    tslFont->LegacyFontSize = 11;
    DrawOutlinedText(HUD, FString(weaponname.c_str()),
                     weaponPos, weaponColor, COLOR_BLACK, true);
    tslFont->LegacyFontSize = TSL_FONT_DEFAULT_SIZE;
}
                    
                    if (Cheat::Esp::Alert)
{
    bool shit = false;

    SDK::FVector MyPosition = Player->CurrentVehicle
        ? Player->CurrentVehicle->RootComponent->RelativeLocation
        : Player->RootComponent->RelativeLocation;

    SDK::FVector EnemyPosition = Cheat::localPlayer->CurrentVehicle
        ? Cheat::localPlayer->CurrentVehicle->RootComponent->RelativeLocation
        : Cheat::localPlayer->RootComponent->RelativeLocation;

    SDK::FVector EntityPos = WorldToRadar(
        Cheat::localController->PlayerCameraManager->CameraCache.POV.Rotation.Yaw,
        MyPosition, EnemyPosition, NULL, NULL,
        Vector3((float)glWidth, (float)glHeight, 0), shit);

    SDK::FVector angle = SDK::FVector();

    Vector3 forward = Vector3(
        (float)(glWidth  / 2) - EntityPos.X,
        (float)(glHeight / 2) - EntityPos.Y,
        0.0f);
    VectorAnglesRadar(forward, angle);

    const auto angle_yaw_rad = DEG2RAD(angle.Y + 180.f);
    const auto new_point_x = (glWidth  / 2) + (30) / 2 * 4 * cosf(angle_yaw_rad);
    const auto new_point_y = (glHeight / 2) + (30) / 2 * 4 * sinf(angle_yaw_rad);

    if (IsVisible)
    {
        // ImU32 IM_COL32(0, 255, 200, 255) → FLinearColor(0, 1, 200/255, 1)
        FLinearColor alertColor = FLinearColor(0.0f, 1.0f, 200.f / 255.f, 1.0f);

        // ImGui: AddCircle(center, radius=5.0f, color, segments=64, thickness=5.0f)
        // HUD:   DrawCircleHelper(HUD, cx, cy, radius, color, segments, thickness)
        DrawCircleHelper(HUD, new_point_x, new_point_y, 5.0f, alertColor, 64, 5.0f);
    }
}
            
            
            

                    if (Cheat::Esp::Name || Cheat::Esp::Distance)
                    {
                        tslFont->LegacyFontSize = 10;

                        float textX = x + (width / 2.0f);
                        float textY = y + totalHeight + 4.0f;

                        if (Cheat::Esp::Name)
                        {
                            if (!Player->bEnsure)
                                DrawOutlinedText(HUD, Player->PlayerName, FVector2D(textX, textY), COLOR_WHITE, COLOR_BLACK, true);
                            else
                                DrawOutlinedText(HUD, FString("Bot"), FVector2D(textX, textY), COLOR_WHITE, COLOR_BLACK, true);

                            textY += 14.0f;
                        }

                        if (Cheat::Esp::Distance)
                        {
                            std::string distanceStr = std::to_string((int)Distance) + " M";
                            DrawOutlinedText(HUD, FString(distanceStr.c_str()), FVector2D(textX, textY), COLOR_YELLOW, COLOR_BLACK, true);
                        }

                        tslFont->LegacyFontSize = TSL_FONT_DEFAULT_SIZE;
                    }
                }
            }
            
            
            
            

            if (Cheat::Esp::Vehicle::Name && i->IsA(ASTExtraVehicleBase::StaticClass()))
            {
                auto Vehicle = (ASTExtraVehicleBase*)i;
                if (!Vehicle->Mesh)
                    continue;

                float Distance = Vehicle->GetDistanceTo(Cheat::localPlayer) / 100.f;

                FVector2D vehiclePos;
                if (W2S(Vehicle->K2_GetActorLocation(), &vehiclePos))
                {
                    float mWidthScale = std::min(0.10f * Distance, 50.f);
                    float mWidth = 70.f - mWidthScale;

                    std::string nameStr = GetVehicleName(Vehicle);
                    std::string distStr = std::to_string((int)Distance) + "M";

                    FLinearColor WhiteColor(1.0f, 1.0f, 0.0f, 1.0f);
                    tslFont->LegacyFontSize = 10;

                    DrawOutlinedText(HUD, FString(nameStr.c_str()), { vehiclePos.X - (mWidth / 2), vehiclePos.Y }, WhiteColor, COLOR_BLACK, true);
                    DrawOutlinedText(HUD, FString(distStr.c_str()), { vehiclePos.X - (mWidth / 2), vehiclePos.Y + 14 }, WhiteColor, COLOR_BLACK, true);

                    tslFont->LegacyFontSize = TSL_FONT_DEFAULT_SIZE;
                }
            }
			
			if (Cheat::Esp::Throwable)
            {
                if (Actor->IsA(ASTExtraGrenadeBase::StaticClass()))
                {
                    auto Grenade = (ASTExtraGrenadeBase*)Actor;
                    if (!Grenade->RootComponent)
                        continue;

                    float Distance = Grenade->GetDistanceTo(Cheat::localPlayer) / 100.f;
                    if (Distance > 50.f)
                        continue;

                    FVector2D grenadePos;
                    if (W2S(Grenade->K2_GetActorLocation(), &grenadePos))
                    {
                        tslFont->LegacyFontSize = 10;

                        DrawOutlinedText(HUD, FString("Nade"), FVector2D(grenadePos.X, grenadePos.Y),
                                         FLinearColor(1.0f, 0.0f, 0.0f, 1.0f), COLOR_BLACK, true);

                        std::string distStr = " " + std::to_string((int)Distance) + "M";
                        DrawOutlinedText(HUD, FString(distStr.c_str()), FVector2D(grenadePos.X, grenadePos.Y + 14),
                                         FLinearColor(1.0f, 0.0f, 0.0f, 1.0f), COLOR_BLACK, true);

                        tslFont->LegacyFontSize = TSL_FONT_DEFAULT_SIZE;
                    }
                }
            }

            if (Cheat::Esp::LootBox)
            {
                if (Actor->IsA(APickUpListWrapperActor::StaticClass()))
                {
                    auto Pick = (APickUpListWrapperActor*)Actor;
                    if (!Pick->RootComponent)
                        continue;

                    float Distance = Pick->GetDistanceTo(Cheat::localPlayer) / 100.f;
                    if (Distance > 50.f)
                        continue;

                    FVector2D boxPos;
                    if (W2S(Pick->K2_GetActorLocation(), &boxPos))
                    {
                        tslFont->LegacyFontSize = 10;

                        DrawOutlinedText(HUD, FString("Death Box"), FVector2D(boxPos.X, boxPos.Y),
                                         FLinearColor(0.0f, 1.0f, 0.0f, 1.0f), COLOR_BLACK, true);

                        std::string distStr = " " + std::to_string((int)Distance) + "M";
                        DrawOutlinedText(HUD, FString(distStr.c_str()), FVector2D(boxPos.X, boxPos.Y + 14),
                                         FLinearColor(0.0f, 1.0f, 0.0f, 1.0f), COLOR_BLACK, true);

                        tslFont->LegacyFontSize = TSL_FONT_DEFAULT_SIZE;
                    }
                }
            }
            
    

            if (Actor->IsA(APickUpWrapperActor::StaticClass()))
            {
                auto PickUp = (APickUpWrapperActor*)Actor;

                if (Items[PickUp->DefineID.TypeSpecificID])
                {
                    auto RootComponent = PickUp->RootComponent;
                    if (!RootComponent)
                        continue;

                    float Distance = PickUp->GetDistanceTo(Cheat::localPlayer) / 100.f;
                    if (Distance > 100.0f)
                        continue;

                    FVector2D itemPos;
                    if (W2S(PickUp->K2_GetActorLocation(), &itemPos))
                    {
                        std::string itemName;
                        uint32_t textColor = 0xFFFFFFFF;

                        for (auto& category : items_data)
                        {
                            for (auto& item : category["Items"])
                            {
                                if (item["itemId"] == PickUp->DefineID.TypeSpecificID)
                                {
                                    itemName = item["itemName"].get<std::string>();
                                    textColor = strtoul(item["itemTextColor"].get<std::string>().c_str(), 0, 16);
                                    break;
                                }
                            }
                        }

                        tslFont->LegacyFontSize = 10;

                        DrawOutlinedText(HUD, FString(itemName.c_str()), FVector2D(itemPos.X, itemPos.Y),
                                         UIntToLinearColor(textColor), COLOR_BLACK, true);

                        std::string distText = " " + std::to_string((int)Distance) + " M";
                        uint32_t distanceColor = 0xFFAAAAAA;
                        DrawOutlinedText(HUD, FString(distText.c_str()), FVector2D(itemPos.X, itemPos.Y + 12.0f),
                                         UIntToLinearColor(distanceColor), COLOR_BLACK, true);

                        tslFont->LegacyFontSize = TSL_FONT_DEFAULT_SIZE;
                    }
                }
            }
        }
        
        
        if (Cheat::Esp::Counter)
        {
            int totalEntities = totalEnemies + totalBots;
            if (totalEntities > 0)
            {
                std::string s = "  " + std::to_string(totalEntities);
                tslFont->LegacyFontSize = 20;
                DrawOutlinedText(HUD, FString(s), FVector2D((float)glWidth / 2.0f - 1, 110),
                                 COLOR_RED, COLOR_BLACK, true);
                tslFont->LegacyFontSize = TSL_FONT_DEFAULT_SIZE;
            }
        }
    }
}

void DrawMemory()
{
    if (Cheat::localPlayer && Cheat::localController)
    {
        if (Cheat::Aimbot::Enable) {
    // 获取瞄准目标
    ASTExtraPlayerCharacter *Target = GetTargetForAimBot();
    // 目标有效时的处理
    if (Target) {
    bool triggerOk = false;
   if (Cheat::Aimbot::Trigger == EAimTrigger::None) {
triggerOk = Cheat::localPlayer->bIsWeaponFiring;
}
if (Cheat::Aimbot::Trigger == EAimTrigger::Scoping) {
triggerOk = Cheat::localPlayer->bIsGunADS;
}
if (Cheat::Aimbot::Trigger == EAimTrigger::Both) {
triggerOk = Cheat::localPlayer->bIsWeaponFiring || Cheat::localPlayer->bIsGunADS;
}
if (triggerOk) {
FVector targetAimPos;
 if (Cheat::Aimbot::Target == EAimTarget::Head) {
 targetAimPos = Target->GetBonePos("Head", {0, 0, 0});
  }

 if (Cheat::Aimbot::Target == EAimTarget::Chest) {
 targetAimPos = Target->GetBonePos("upperarm_r", {0, 0, 0});
}
switch (Cheat::Aimbot::Target == EAimTarget::Head) {
                            case 1:
                                targetAimPos = Target->GetBonePos("Head", {});
                                break;
                            case 2:
                                targetAimPos = Target->GetBonePos("pelvis", {});
                                break;
                            case 3:
                                targetAimPos = Target->GetBonePos("calf_l", {});
                                break;
                            case 4:
                                targetAimPos = Target->GetBonePos("calf_r", {});
                                break;
                            case 5:
                                targetAimPos = Target->GetBonePos("lowerarm_l", {});
                                break;
                            case 6:
                                targetAimPos = Target->GetBonePos("lowerarm_r", {});
                                break;
                            case 7:
                                targetAimPos = Target->GetBonePos("upperarm_l", {});
                                break;
                            case 8:
                                targetAimPos = Target->GetBonePos("upperarm_r", {});
                                break;
                            case 9:
                                targetAimPos = Target->GetBonePos("thigh_l", {});
                                break;
                            case 10:
                                targetAimPos = Target->GetBonePos("thigh_r", {});
                                break;
                            case 11:
                                targetAimPos = Target->GetBonePos("foot_l", {});
                                break;
                            case 12:
                                targetAimPos = Target->GetBonePos("foot_r", {});
                                break;
                            default:
                                targetAimPos = Target->GetBonePos("Head", {});
                                break;
                        }
                        if(Cheat::Aimbot::Target == EAimTarget::Chest){
                        if(算法 == 0) {
                        targetAimPos = Target->GetBonePos("Head", {});//头
                        }else if(算法 == 1) {
                        targetAimPos = Target->GetBonePos("spine_03", {});//脖子
                        }else if(算法 == 2){
                        targetAimPos = Target->GetBonePos("pelvis", {});//屁股
                        }else if(算法 == 3){
                        targetAimPos = Target->GetBonePos("calf_l", {});//左小腿
                        }else if(算法 == 4){
                        targetAimPos = Target->GetBonePos("calf_r", {});//右小腿
                        }else if(算法 == 5){
                        targetAimPos = Target->GetBonePos("lowerarm_l", {});//左小臂
                        }else if(算法 == 6){
                        targetAimPos = Target->GetBonePos("lowerarm_r", {});//右小臂
                        }else if(算法 == 7){
                        targetAimPos = Target->GetBonePos("upperarm_l", {});//左上臂
                        }else if(算法 == 8){
                        targetAimPos = Target->GetBonePos("upperarm_r", {});//右上臂
                        }else if(算法 == 9) {
                        targetAimPos = Target->GetBonePos("thigh_l", {});//左大腿
                        }else if(算法 == 10) {
                        targetAimPos = Target->GetBonePos("thigh_r", {});//右大腿
                        }else if(算法 == 11) {
                        targetAimPos = Target->GetBonePos("foot_l", {});//左脚
                        }else if(算法 == 12){
                        targetAimPos = Target->GetBonePos("foot_r", {});//右脚
                        }
                        }        
                        /*
            if (targetAimPos.X > 0 && targetAimPos.Y > 0 && targetAimPos.Z > 0) {
    auto WeaponManagerComponent = Cheat::localPlayer->WeaponManagerComponent;
    if (WeaponManagerComponent) {
        auto propSlot = WeaponManagerComponent->GetCurrentUsingPropSlot();
        if ((int) propSlot.GetValue() >= 1 && (int) propSlot.GetValue() <= 3) {
            auto CurrentWeaponReplicated = (ASTExtraShootWeapon *) WeaponManagerComponent->CurrentWeaponReplicated;
            if (CurrentWeaponReplicated) {
                auto ShootWeaponComponent = CurrentWeaponReplicated->ShootWeaponComponent;
                auto ShootWeaponEffectComp = CurrentWeaponReplicated->ShootWeaponEffectComp;
                if (ShootWeaponComponent) {
                    UShootWeaponEntity *ShootWeaponEntityComponent = ShootWeaponComponent->ShootWeaponEntityComponent;
                    if (ShootWeaponEntityComponent) {
                        // Get bullet fire speed using offset 0x408
                        float BulletFireSpeed = *(float*)((uintptr_t)ShootWeaponEntityComponent + 0x560);
                        
                        ASTExtraVehicleBase *CurrentVehicle = Target->CurrentVehicle;
                        if (CurrentVehicle) {
                            FVector LinearVelocity = CurrentVehicle->ReplicatedMovement.LinearVelocity;
                            float dist = Cheat::localPlayer->GetDistanceTo(Target);
                            auto timeToTravel = dist / BulletFireSpeed;  // Using BulletFireSpeed instead of BulletRange
                            targetAimPos = UKismetMathLibrary::Add_VectorVector(targetAimPos, UKismetMathLibrary::Multiply_VectorFloat(LinearVelocity, timeToTravel));
                            targetAimPos.Z += LinearVelocity.Z * timeToTravel + 0.5 * 573.f * timeToTravel * timeToTravel;
                        } else {
                            FVector Velocity = Target->GetVelocity();
                            float dist = Cheat::localPlayer->GetDistanceTo(Target);
                            auto timeToTravel = dist / BulletFireSpeed;  // Using BulletFireSpeed instead of BulletRange
                            targetAimPos = UKismetMathLibrary::Add_VectorVector(targetAimPos, UKismetMathLibrary::Multiply_VectorFloat(Velocity, timeToTravel));
                            targetAimPos.Z += Velocity.Z * timeToTravel + 0.5 * 573.f * timeToTravel * timeToTravel;
                        }
                        
                        
                        
                        if (Cheat::localPlayer->bIsGunADS && Cheat::localPlayer->bIsWeaponFiring) {
                                float dist = Cheat::localPlayer->GetDistanceTo(Target) / 100.f;
                                targetAimPos.Z -= dist * Cheat::Aimbot::RecoilSet;
                            }

                            if (Cheat::localPlayer->bIsWeaponFiring) {
                                // Camera position & target direction
                                FVector gunlocation = Cheat::localController->PlayerCameraManager->CameraCache.POV.Location;
                                FVector dir = targetAimPos - gunlocation;

                                // Normalize
                                float len = sqrtf(dir.X * dir.X + dir.Y * dir.Y + dir.Z * dir.Z);
                                if (len > 0.001f) {
                                    dir.X /= len;
                                    dir.Y /= len;
                                    dir.Z /= len;
                                }

                                // Convert direction → pitch & yaw
                                FRotator aimrotation;
                                aimrotation.Yaw   = atan2f(dir.Y, dir.X) * (180.f / PI_F);
                                aimrotation.Pitch = atan2f(dir.Z, sqrtf(dir.X * dir.X + dir.Y * dir.Y)) * (180.f / PI_F);
                                aimrotation.Roll  = 0;

                                FRotator gunrotaton = Cheat::localController->PlayerCameraManager->CameraCache.POV.Rotation;

                                FRotator deltaRotation;
                                deltaRotation.Pitch = aimrotation.Pitch - gunrotaton.Pitch;
                                deltaRotation.Yaw   = aimrotation.Yaw - gunrotaton.Yaw;
                                deltaRotation.Roll  = 0;

                                ClampAngles(deltaRotation);

                                // Smooth aim
                                float smoothFactor = Cheat::Aimbot::Smoothing;
                                deltaRotation.Pitch /= smoothFactor;
                                deltaRotation.Yaw   /= smoothFactor;

                                Cheat::localController->AddYawInput(deltaRotation.Yaw);
                                Cheat::localController->AddPitchInput(deltaRotation.Pitch);
                        
                        }
                    }
                }
            }
        }
    }
}
*/
auto WeaponManagerComponent = Cheat::localPlayer->WeaponManagerComponent;
if (WeaponManagerComponent)
{
    auto propSlot = WeaponManagerComponent->GetCurrentUsingPropSlot();
    if ((int)propSlot.GetValue() >= 1 && (int)propSlot.GetValue() <= 3)
    {
        auto CurrentWeaponReplicated = (ASTExtraShootWeapon *)WeaponManagerComponent->CurrentWeaponReplicated;
        if (CurrentWeaponReplicated)
        {
            auto ShootWeaponComponent = CurrentWeaponReplicated->ShootWeaponComponent;
            if (ShootWeaponComponent)
            {
                UShootWeaponEntity *ShootWeaponEntityComponent = ShootWeaponComponent->ShootWeaponEntityComponent;
                if (ShootWeaponEntityComponent)
                {
                    float BulletFireSpeed = *(float*)((uintptr_t)ShootWeaponEntityComponent + 0x560);

                    ASTExtraVehicleBase *CurrentVehicle = Target->CurrentVehicle;
                    float dist = Cheat::localPlayer->GetDistanceTo(Target);
                    auto timeToTravel = dist / ShootWeaponEntityComponent->BulletFireSpeed;

                    if (CurrentVehicle)
                    {
                        FVector LinearVelocity = CurrentVehicle->ReplicatedMovement.LinearVelocity;
                        targetAimPos = UKismetMathLibrary::Add_VectorVector(
                            targetAimPos,
                            UKismetMathLibrary::Multiply_VectorFloat(LinearVelocity, timeToTravel));
                    }
                    else
                    {
                        FVector Velocity = Target->GetVelocity();
                        targetAimPos = UKismetMathLibrary::Add_VectorVector(
                            targetAimPos,
                            UKismetMathLibrary::Multiply_VectorFloat(Velocity, timeToTravel));
                    }

                    if (Cheat::localPlayer->bIsWeaponFiring)
                    {
                        float distRecoil = Cheat::localPlayer->GetDistanceTo(Target) / 100.f;
                        targetAimPos.Z -= distRecoil * Cheat::Aimbot::RecoilSet;
                    }

                    FVector fDir = UKismetMathLibrary::Subtract_VectorVector(
                        targetAimPos,
                        Cheat::localController->PlayerCameraManager->CameraCache.POV.Location);

                    FRotator Yaptr = UKismetMathLibrary::Conv_VectorToRotator(fDir);
                    FRotator CpYaT = Cheat::localController->PlayerCameraManager->CameraCache.POV.Rotation;

                    Yaptr.Pitch -= CpYaT.Pitch;
                    Yaptr.Yaw   -= CpYaT.Yaw;
                    Yaptr.Roll   = 0.f;

                    NekoHook(Yaptr);

                    float smoothFactor = Cheat::Aimbot::Smoothing;
                    if (smoothFactor < 1.f) smoothFactor = 1.f;

                    Yaptr.Pitch /= smoothFactor;
                    Yaptr.Yaw   /= smoothFactor;

                    Cheat::localPlayer->AddControllerYawInput(Yaptr.Yaw);
                    Cheat::localPlayer->AddControllerPitchInput(Yaptr.Pitch);
                }
            }
        }
    }
}






        }
    }
}

	
        if (Cheat::Memory::Hit)
        {
            TriggerHitEffect();
        }
        
        
        if (Cheat::Memory::IslandBp)
        {
MemoryPatch::createWithHex("libhdmpve.so",0x1B7504,"C0 03 5F D6").Modify();//𝐎𝐧
MemoryPatch::createWithHex("libhdmpve.so",0x131D30,"C0 03 5F D6").Modify();//𝐎𝐧
}else{ 
MemoryPatch::createWithHex("libhdmpve.so",0x1B7504,"FF 83 00 D1").Modify();//𝐎𝐟𝐟
MemoryPatch::createWithHex("libhdmpve.so",0x131D30,"FF 83 04 D1").Modify();//𝐎𝐟𝐟
}



        if (Cheat::Memory::Small)
        {
            auto WeaponManagerComponent = Cheat::localPlayer->WeaponManagerComponent;

            if (WeaponManagerComponent)
            {
                auto propSlot = WeaponManagerComponent->GetCurrentUsingPropSlot();

                if ((int)propSlot.GetValue() >= 1 && (int)propSlot.GetValue() <= 3)
                {
                    auto CurrentWeaponReplicated = (ASTExtraShootWeapon*)WeaponManagerComponent->CurrentWeaponReplicated;

                    if (CurrentWeaponReplicated)
                    {
                        auto ShootWeaponComponent = CurrentWeaponReplicated->ShootWeaponComponent;

                        if (ShootWeaponComponent)
                        {
                            UShootWeaponEntity* ShootWeaponEntityComponent = ShootWeaponComponent->ShootWeaponEntityComponent;

                            if (ShootWeaponEntityComponent)
                            {
                            
                            if (Cheat::Memory::Small)
                                {
                                 FLinearColor interpolatedColor = RandomColor();
                                 Cheat::localController->CrossHairColor = interpolatedColor;
                                 ShootWeaponEntityComponent->GameDeviationFactor = 0.0f;
                                }
                         
                          
                            }
                        }
                    }
                }
            }
        }
    }
}

void AutoEspOn() 
{
    Cheat::Esp::Line = true;
    Cheat::Esp::Name = true;
    Cheat::Esp::Distance = true;
    Cheat::Esp::Health = true;
    Cheat::Esp::Skeleton = true;
    //Cheat::Esp::Box = true;
	Cheat::Esp::LootBox = true;
	Cheat::Esp::Throwable = true;
	Cheat::Esp::Counter = true;
    Cheat::Esp::Vehicle::Name = true;
    Cheat::Esp::Alert = true;
    Cheat::Esp::WeaponName = true;
    
    Cheat::Aimbot::Radius = 130.0f;
    Cheat::Aimbot::RecoilSet = 1.045f;
    Cheat::Aimbot::IgnoreKnock = true;
    Cheat::Aimbot::VisCheck = true;
    
    Cheat::Aimbot::Smoothing = 4.0;
    
    Cheat::BulletTrack::TrackingAccuracy = 1;
    Cheat::Aimbot::Range = 120.0f;
   
    for (auto &i : items_data) 
    {
        int itemCount = 0;
        for (auto &item : i[("Items")]) 
        {
            item[("itemName")].get<std::string>().c_str();
            Items[item[("itemId")].get<int>()] = true;
            itemCount++;

            if (itemCount % 4 != 0 && &item != &i[("Items")].back()){}
        }
    }
}


 
EGLBoolean (*orig_eglSwapBuffers)(EGLDisplay dpy, EGLSurface surface);
EGLBoolean _eglSwapBuffers(EGLDisplay dpy, EGLSurface surface) {
    using KennyDiagnostics::Severity;
    const auto forward=[&]{return orig_eglSwapBuffers?orig_eglSwapBuffers(dpy,surface):EGL_FALSE;};
    if(!orig_eglSwapBuffers){KennyDiagnostics::Once(30,Severity::Error,0,false,"Swap forwarding unavailable");return EGL_FALSE;}
    auto* app=PresentationApp.load(std::memory_order_acquire);
    if(!app){KennyDiagnostics::Once(4,Severity::Warning,0,false,"Application context not available; UI deferred");return forward();}
    static bool renderStorageAttempted=false;
    if(!renderStorageAttempted&&app->activity&&app->activity->internalDataPath){
        renderStorageAttempted=true;
        const bool stored=KennyDiagnostics::SetStorage(app->activity->internalDataPath);
        KennyDiagnostics::Once(27,stored?Severity::Info:Severity::Warning,stored?0:errno,stored,stored?"App-private persistent diagnostics ready":"Private diagnostic storage unavailable; retain logcat");
    }
    auto* window=app->window;auto* configuration=app->config;
    if(!window||!configuration){KennyDiagnostics::Once(5,Severity::Warning,0,false,"Native window/configuration not available; UI deferred");return forward();}
    KennyDiagnostics::Once(5,Severity::Info,0,true,"Native window/configuration available");
    const EGLContext current=eglGetCurrentContext();
    if(dpy==EGL_NO_DISPLAY||surface==EGL_NO_SURFACE||eglGetCurrentDisplay()!=dpy||eglGetCurrentSurface(EGL_DRAW)!=surface){
        KennyDiagnostics::Once(6,Severity::Warning,eglGetError(),false,"EGL display/draw surface not current; UI deferred");return forward();
    }
    if(current==EGL_NO_CONTEXT){KennyDiagnostics::Once(7,Severity::Warning,0,false,"No current EGL context; UI deferred");return forward();}
    KennyDiagnostics::Once(6,Severity::Info,0,true,"EGL display/draw surface current");
    KennyDiagnostics::Once(7,Severity::Info,0,true,"EGL context available");
    EGLint width=0,height=0;
    if(!eglQuerySurface(dpy,surface,EGL_WIDTH,&width)||!eglQuerySurface(dpy,surface,EGL_HEIGHT,&height)||width<=0||height<=0){
        KennyDiagnostics::Once(29,Severity::Warning,eglGetError(),false,"EGL dimensions unavailable; UI deferred");return forward();
    }
    KennyStartup::RenderGuard rendering;if(!rendering.acquired)return forward();
    glWidth=width;glHeight=height;
    screenWidth=ANativeWindow_getWidth(window);screenHeight=ANativeWindow_getHeight(window);
    if(screenWidth<=0||screenHeight<=0){rendering.Release();return forward();}
    density=AConfiguration_getDensity(configuration);
    if(density<=0||density>1000)density=160;
    static ImGuiContext* uiContext=nullptr;
    static EGLContext rendererContext=EGL_NO_CONTEXT;
    static EGLDisplay rendererDisplay=EGL_NO_DISPLAY;
    static KennyMenu::State menuState;
    static KennyLauncher::State launcher;
    static KennyPresentation::AndroidBackend presentation;
    static KennyAudio::AndroidBackend uiAudio;
    static bool stagedCharacters=false,modulesLogged=false,rendererFailed=false;
    ImGuiContext* previous=ImGui::GetCurrentContext();
    struct RestoreContext {ImGuiContext*& previous;~RestoreContext(){ImGui::SetCurrentContext(previous);}} restore{previous};
    if(uiContext&&rendererContext!=current){
        EGLint ownerVersion=0;
        if(eglQueryContext(rendererDisplay,rendererContext,EGL_CONTEXT_CLIENT_VERSION,&ownerVersion)==EGL_TRUE){
            // Another live context is not context loss. Retain the existing
            // resources instead of allocating new textures on every swap.
            KennyDiagnostics::Once(40,Severity::Warning,0,false,"Secondary live EGL context; UI remains on its original owner");
            rendering.Release();return forward();
        }
        if(previous==uiContext)previous=nullptr;
        ImGui::SetCurrentContext(uiContext);
        launcher.logo.Clear();menuState.characters.ClearTextures(true);
        menuState.animeVideoFrame={};menuState.brandLogo={};presentation.Clear(true);
        ImGui_ImplOpenGL3_ForgetDeviceObjects();ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplAndroid_Shutdown();ImGui::DestroyContext(uiContext);
        uiContext=nullptr;initImGui=false;KennyMenu::Font=nullptr;font2=nullptr;
        KennyDiagnostics::Event(28,Severity::Warning,0,true,"Graphics context changed; UI resources rebuilt without deleting foreign GL names");
    }
    if(rendererContext!=current)rendererFailed=false;
    rendererContext=current;
    rendererDisplay=dpy;
    if(rendererFailed){rendering.Release();return forward();}
    KennyDiagnostics::Once(31,Severity::Info,0,true,"Application/native window/EGL preconditions ready");
    // ----------------------------------------------------------------
    // One-time init
    // ----------------------------------------------------------------
    if (!initImGui) {
        GLint major=0;glGetIntegerv(GL_MAJOR_VERSION,&major);
        if(major<3||!glGetString(GL_VERSION)){rendererFailed=true;KennyDiagnostics::Event(7,Severity::Error,0,false,"Current graphics context is not usable GLES3");rendering.Release();return forward();}
        KennyDiagnostics::Once(8,Severity::Info,0,true,"ImGui context creation started");
        uiContext=ImGui::CreateContext();
        if(!uiContext){rendererFailed=true;KennyDiagnostics::Event(9,Severity::Error,ENOMEM,false,"ImGui context creation failed");rendering.Release();return forward();}
        ImGui::SetCurrentContext(uiContext);
        KennyDiagnostics::Once(9,Severity::Info,0,true,"ImGui context created");
        KennyDiagnostics::Once(10,Severity::Info,0,true,"Embedded font initialization started");
        ImGuiIO& io = ImGui::GetIO();

        // Icons config (merge into base font)
        ImFontConfig icons_cfg;
        icons_cfg.FontDataOwnedByAtlas = false;
        icons_cfg.MergeMode   = true;
        icons_cfg.PixelSnapH  = true;
        icons_cfg.OversampleH = 2;
        icons_cfg.OversampleV = 2;
        static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };

        // Base UI font
        ImFontConfig base_cfg;
        base_cfg.FontDataOwnedByAtlas = false;
        io.Fonts->AddFontFromMemoryTTF((void*)Custom_data, Custom_size, 16.0f,
                                       &base_cfg, io.Fonts->GetGlyphRangesDefault());

        // Icon font merged into base
        io.Fonts->AddFontFromMemoryTTF((void*)fontAwesome, sizeof(fontAwesome),
                                       15.0f, &icons_cfg, icons_ranges);

        // Small ESP/mono font (kept for existing usage)
        ImFontConfig esp_cfg;
        esp_cfg.FontDataOwnedByAtlas = false;
        font2 = io.Fonts->AddFontFromMemoryTTF((void*)voidespfont,
                                               sizeof(voidespfont), 16.0f, &esp_cfg);

        // Default fallback
        ImFontConfig cfg;
        cfg.SizePixels = ((float)density / 20.0f);
        io.Fonts->AddFontDefault(&cfg);

        // Bake the existing typeface at header resolution once. Only the menu
        // selects this font; the original base, ESP, and fallback fonts remain.
        ImFontConfig menu_cfg;
        menu_cfg.FontDataOwnedByAtlas = false;
        KennyMenu::Font = io.Fonts->AddFontFromMemoryTTF((void*)Custom_data, Custom_size,
                                                        32.0f, &menu_cfg);
        ImFontConfig menu_icons = icons_cfg;
        menu_icons.FontDataOwnedByAtlas = false;
        io.Fonts->AddFontFromMemoryTTF((void*)fontAwesome, sizeof(fontAwesome),
                                       30.0f, &menu_icons, icons_ranges);

        if(!io.Fonts->Build()||!font2||!KennyMenu::Font){
            KennyDiagnostics::Event(11,Severity::Error,0,false,"Font atlas build failed; UI deferred");
            ImGui::DestroyContext(uiContext);uiContext=nullptr;KennyMenu::Font=nullptr;font2=nullptr;
            rendererFailed=true;rendering.Release();return forward();
        }
        KennyDiagnostics::Once(11,Severity::Info,0,true,"Embedded font atlas built");

        // Apply the KennyPvtHax black/crimson theme
        Claude::Apply();

        KennyDiagnostics::Once(12,Severity::Info,0,true,"Android/OpenGL backend initialization started");
        const bool androidReady=ImGui_ImplAndroid_Init();
        const bool rendererReady=androidReady&&ImGui_ImplOpenGL3_Init(OBFUSCATE("#version 300 es"));
        const bool devicesReady=rendererReady&&ImGui_ImplOpenGL3_CreateDeviceObjects();
        if(!devicesReady){
            KennyDiagnostics::Event(13,Severity::Error,int(glGetError()),false,"Android/OpenGL backend initialization failed; UI deferred");
            if(rendererReady)ImGui_ImplOpenGL3_Shutdown();if(androidReady)ImGui_ImplAndroid_Shutdown();
            ImGui::DestroyContext(uiContext);uiContext=nullptr;KennyMenu::Font=nullptr;font2=nullptr;
            rendererFailed=true;rendering.Release();return forward();
        }
        initImGui = true;
        KennyDiagnostics::Once(13,Severity::Info,0,true,"Android/OpenGL backend initialized");
    }

    ImGui::SetCurrentContext(uiContext);
    ImGuiIO& io = ImGui::GetIO();
    KennyStartup::Inputs().Drain([&](const KennyStartup::Input& input){
        if(input.kind==KennyStartup::Input::Motion){
            if(std::isfinite(input.x)&&std::isfinite(input.y))io.MousePos=ImVec2(input.x*glWidth/screenWidth,input.y*glHeight/screenHeight);
            if(input.transition)io.MouseDown[0]=input.down;
        }else if(input.code>=0&&input.code<IM_ARRAYSIZE(io.KeysDown)){
            io.KeysDown[input.code]=input.down;
            io.KeyCtrl=(input.modifiers&AMETA_CTRL_ON)!=0;io.KeyShift=(input.modifiers&AMETA_SHIFT_ON)!=0;io.KeyAlt=(input.modifiers&AMETA_ALT_ON)!=0;
        }
    });
    KennyDiagnostics::Once(19,Severity::Info,0,true,"First ImGui frame started");
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame(glWidth, glHeight);
    ImGui::NewFrame();

    const char* privateDirectory=app->activity?app->activity->internalDataPath:nullptr;
    if(!KPH_DIAGNOSTIC_NO_PREFERENCES&&privateDirectory&&!menuState.storage.configured){
        KennyDiagnostics::Event(14,Severity::Info,0,false,"Appearance load started");
        menuState.storage.Configure(privateDirectory,menuState.appearance);
        KennyDiagnostics::Event(14,menuState.storage.available?Severity::Info:Severity::Warning,0,menuState.storage.available,"%s",menuState.storage.status);
    }
    KennyDiagnostics::Once(14,Severity::Info,0,true,"Appearance initialization reached (see isolation/storage availability)");
    if(!stagedCharacters&&privateDirectory&&app->activity){
        stagedCharacters=true;
        KennyDiagnostics::Event(16,Severity::Info,0,false,"APK pack staging started");
        const bool staged=KennyCharacters::StageAPK(app->activity->assetManager,privateDirectory);
        KennyPresentation::StageAPK(app->activity->assetManager,privateDirectory);
        KennyDiagnostics::Once(16,staged?Severity::Info:Severity::Warning,0,staged,staged?"APK pack staging completed":"APK pack unavailable; safe missing-asset fallback");
    }
    if(privateDirectory&&!menuState.characters.configured){
        KennyDiagnostics::Event(15,Severity::Info,0,false,"Character registry load started");
        menuState.characters.Configure(privateDirectory);
        KennyDiagnostics::Event(15,Severity::Info,0,true,"Registry load completed: characters=%u, decodedBytes=%zu",menuState.characters.count,menuState.characters.decodedBytes);
    }
    KennyDiagnostics::Once(15,Severity::Info,0,true,"Character registry initialization reached; missing packs remain optional");
    menuState.characters.upload=KPH_DIAGNOSTIC_NO_ARTWORK?nullptr:KennyCharacters::UploadGL;
    menuState.characters.release=KennyCharacters::ReleaseGL;
    if(!modulesLogged&&!KPH_DIAGNOSTIC_NO_AUDIO)KennyDiagnostics::Event(17,Severity::Info,0,false,"Optional OpenSL audio initialization started");
    if(!KPH_DIAGNOSTIC_NO_AUDIO)uiAudio.Initialize();
    menuState.audio=uiAudio.Ready()?&uiAudio.dispatcher:nullptr;
    menuState.audioStatus=KPH_DIAGNOSTIC_NO_AUDIO?"UI audio isolated in this diagnostic build.":uiAudio.Status();
    KennyDiagnostics::Once(17,uiAudio.Ready()?Severity::Info:Severity::Warning,uiAudio.LastError(),uiAudio.Ready(),menuState.audioStatus);
    if(KPH_DIAGNOSTIC_CLASSIC)menuState.appearance.theme=KennyAppearance::Theme::Classic;
    if(!modulesLogged)KennyDiagnostics::Event(34,Severity::Info,0,false,"Character textures/voice routing preparation started");
    menuState.characters.Prepare(menuState.appearance,menuState.audio);
    KennyDiagnostics::Once(34,Severity::Info,0,true,"Character textures/voice routing preparation completed");
    if(!modulesLogged){
        modulesLogged=true;
        KennyDiagnostics::Event(32,Severity::Info,0,true,"Isolation: audio=%d artwork=%d preferences=%d classic=%d menu=%d",KPH_DIAGNOSTIC_NO_AUDIO,KPH_DIAGNOSTIC_NO_ARTWORK,KPH_DIAGNOSTIC_NO_PREFERENCES,KPH_DIAGNOSTIC_CLASSIC,KPH_DIAGNOSTIC_NO_MENU);
    }
    auto& selectedCharacter=menuState.characters.Selected(menuState.appearance);
    if(!KPH_DIAGNOSTIC_NO_ARTWORK){
        presentation.assets.Configure(privateDirectory);
        const bool videoVisible=menuState.appearance.theme==KennyAppearance::Theme::Anime && menuState.appearance.animeVideo && launcher.DrawMenu() && !KPH_DIAGNOSTIC_NO_MENU;
        menuState.animeVideoFrame=presentation.Pump(app->activity,videoVisible,!menuState.appearance.reducedMotion);
        menuState.videoStatus=presentation.Status();
    }
    if(menuState.appearance.theme==KennyAppearance::Theme::Anime && menuState.appearance.characterLauncher && selectedCharacter.launcherTexture.Valid())
        launcher.logo.Set(selectedCharacter.launcherTexture);
    else if(!KPH_DIAGNOSTIC_NO_ARTWORK && presentation.assets.logoTexture.Valid())launcher.logo.Set(presentation.assets.logoTexture);
    else launcher.logo.Clear();
    menuState.brandLogo=KPH_DIAGNOSTIC_NO_ARTWORK?KennyThemeBackground::ArtworkFrame{}:presentation.assets.logoTexture;
    if(!KPH_DIAGNOSTIC_NO_MENU)KennyLauncher::Draw(launcher,menuState.appearance,menuState.audio,
                        ImVec2(static_cast<float>(glWidth),static_cast<float>(glHeight)));
    launcher.Advance(io.DeltaTime,menuState.appearance.reducedMotion);
    KennyDiagnostics::Once(18,Severity::Info,0,true,"Launcher initialization/draw reached");
    if (!KPH_DIAGNOSTIC_NO_MENU && launcher.DrawMenu()) {
        bool opened=true;
        KennyMenu::Draw(menuState, opened, Settings::Tab,
                        ImVec2(static_cast<float>(glWidth), static_cast<float>(glHeight)), [] {
            if (Settings::Tab == 1) {
                if (KennyPanels::Begin("##players", 3)) {
                    KennyPanels::Section("Player");
                    KennyControls::Checkbox("ESP line",     &Cheat::Esp::Line);
                    KennyControls::Checkbox("ESP skeleton", &Cheat::Esp::Skeleton);
                    KennyControls::Checkbox("ESP health",   &Cheat::Esp::Health);
                    KennyControls::Checkbox("ESP box",      &Cheat::Esp::Box);
                    KennyPanels::EndSection();
                    KennyPanels::Section("Labels");
                    KennyControls::Checkbox("ESP name",     &Cheat::Esp::Name);
                    KennyControls::Checkbox("ESP distance", &Cheat::Esp::Distance);
                    KennyControls::Checkbox("Counter",      &Cheat::Esp::Counter);
                    KennyPanels::EndSection();
                    KennyPanels::Section("World");
                    KennyControls::Checkbox("Alert",        &Cheat::Esp::Alert);
                    KennyControls::Checkbox("Loot box",     &Cheat::Esp::LootBox);
                    KennyControls::Checkbox("Vehicle name", &Cheat::Esp::Vehicle::Name);
                    KennyPanels::EndSection();
                    KennyPanels::End();
                }
            }
            else if (Settings::Tab == 2) {
                if (KennyPanels::Begin("##world", 2, 12.0f)) {
                    KennyPanels::Section("Threats & targeting");
                    KennyControls::Checkbox("Throwable",    &Cheat::Esp::Throwable);
                    KennyControls::Checkbox("Target line",  &Cheat::Esp::Target);
                    KennyPanels::EndSection();
                    KennyPanels::Section("Equipment");
                    KennyControls::Checkbox("Enemy weapon", &Cheat::Esp::WeaponName);
                    KennyPanels::EndSection();
                    KennyPanels::End();
                }
            }
            else if (Settings::Tab == 3) {
                if (KennyPanels::Begin("##aim", 2, 12.0f)) {
                    KennyPanels::Section("Targeting");
                    KennyControls::Checkbox("Enable aimbot", &Cheat::Aimbot::Enable);
                    KennyControls::SliderFloat("Aim range", &Cheat::Aimbot::Range, 0.0f, 400.0f, "%.0f m");
                    KennyPanels::EndSection();
                    KennyPanels::Section("Filtering");
                    KennyControls::Checkbox("Visibility check", &Cheat::Aimbot::VisCheck);
                    KennyControls::Checkbox("Ignore knocked", &Cheat::Aimbot::IgnoreKnock);
                    KennyControls::Checkbox("Ignore bot", &Cheat::Aimbot::IgnoreBot);
                    KennyPanels::EndSection();
                    KennyPanels::Section("Tuning");
                    KennyControls::SliderFloat("Aim smoothing", &Cheat::Aimbot::Smoothing, 1.0f, 4.0f, "%.0f");
                    KennyControls::SliderFloat("Recoil compensation", &Cheat::Aimbot::RecoilSet, 0.0f, 2.0f);
                    KennyPanels::EndSection();
                    KennyPanels::Section("Field of view");
                    KennyControls::Checkbox("Enable FOV", &Cheat::Aimbot::EnableFov);
                    if (Cheat::Aimbot::EnableFov) {
                        KennyControls::SliderFloat("Aim FOV", &Cheat::Aimbot::Radius, 0.0f, 400.0f, "%.0f");
                        KennyControls::Checkbox("Show FOV circle", &Cheat::Aimbot::ShowFovCircle);
                    }
                    KennyPanels::EndSection();
                    KennyPanels::End();
                }
            }
            else if (Settings::Tab == 4) {
                if (KennyPanels::Begin("##tracking", 3, 10.0f, "Force headshot on full")) {
                    KennyPanels::Section("Tracking");
                    KennyControls::Checkbox("Enable bullet track", &Cheat::BulletTrack::Enable);
                    KennyControls::Checkbox("Force headshot on full", &Cheat::BulletTrack::ForceHeadshotWhenFull);
                    KennyControls::SliderInt("Tracking accuracy", &Cheat::BulletTrack::TrackingAccuracy, 1, 3, "%d/3");
                    KennyPanels::EndSection();
                    KennyPanels::Section("Filtering");
                    KennyControls::Checkbox("Visibility check", &Cheat::Aimbot::VisCheck);
                    KennyControls::Checkbox("Ignore knocked", &Cheat::Aimbot::IgnoreKnock);
                    KennyControls::Checkbox("Ignore bot", &Cheat::Aimbot::IgnoreBot);
                    KennyPanels::EndSection();
                    KennyPanels::Section("Field of view");
                    KennyControls::Checkbox("Enable FOV", &Cheat::Aimbot::EnableFov);
                    if (Cheat::Aimbot::EnableFov) {
                        KennyControls::SliderFloat("Aim FOV", &Cheat::Aimbot::Radius, 0.0f, 400.0f, "%.0f");
                        KennyControls::Checkbox("Show FOV circle", &Cheat::Aimbot::ShowFovCircle);
                    }
                    KennyControls::SliderFloat("Aim range", &Cheat::Aimbot::Range, 0.0f, 400.0f, "%.0f m");
                    KennyPanels::EndSection();
                    KennyPanels::End();
                }
            }
            else if (Settings::Tab == 5) {
                if (KennyPanels::Begin("##extras", 2, 12.0f)) {
                    KennyPanels::Section("Presentation");
                    KennyControls::Checkbox("Small cross", &Cheat::Memory::Small);
                    KennyControls::Checkbox("X-hit effect", &Cheat::Memory::Hit);
                    KennyControls::Checkbox("iPad view", &Cheat::Memory::IPad);
                    KennyPanels::EndSection();
                    KennyPanels::Section("Utilities");
                    KennyControls::Checkbox("6-hour fixer", &Cheat::Memory::IslandBp);
                    if (KennyControls::Button("Guest Reset")) {
                        ResetLogin();
                    }
                    KennyPanels::EndSection();
                    KennyPanels::End();
                }
            }
        },launcher.alpha,launcher.target);
        KennyDiagnostics::Once(21,Severity::Info,0,true,"First menu rendering completed");
        if(!opened)launcher.Request(false,menuState.appearance,menuState.audio,ImGui::GetTime());
    }

    // Completed audio/appearance changes also flush after menu closure.
    // Flush only completed appearance edits; hidden themes do no rendering.
    if(!KPH_DIAGNOSTIC_NO_PREFERENCES&&!KPH_DIAGNOSTIC_CLASSIC)menuState.storage.Sync(menuState.appearance,!launcher.target || !ImGui::IsAnyItemActive());
    if(!KPH_DIAGNOSTIC_NO_AUDIO)uiAudio.Pump(menuState.appearance);
    if(uiAudio.LastError())KennyDiagnostics::Once(33,Severity::Warning,uiAudio.LastError(),false,uiAudio.Status());

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    KennyDiagnostics::Once(20,Severity::Info,0,true,"First ImGui frame and GL submission completed");
    rendering.Release();
    return forward();
}

void (*oReceiveDrawHUD)(AHUD *pHUD, int SizeX, int SizeY);
void hkReceiveDrawHUD(AHUD *pHUD, int SizeX, int SizeY)
{
    if (pHUD)
    {
        RenderESPPRIVATE(pHUD, SizeX, SizeY);
        DrawHUD(pHUD);
        DrawMemory();
    }
    oReceiveDrawHUD(pHUD, SizeX, SizeY);
}

/*
void* (*oProcessEvent)(UObject*, UFunction*, void*);
void* hkProcessEvent(UObject* pObj, UFunction* pFunc, void* pArgs) 
{
    if (!pObj || !pFunc) 
        return oProcessEvent(pObj, pFunc, pArgs);

    const char* EngineHUD = ("Function Engine.HUD.ReceiveDrawHUD");
    if (pFunc->GetFullName() == EngineHUD) 
    {
        AHUD* pHUD = (AHUD*)pObj;
        if (pHUD) 
        {
            auto Params = (AHUD_ReceiveDrawHUD_Params*)pArgs;
            if (Params) 
            {
                RenderESPPRIVATE(pHUD, Params->SizeX, Params->SizeY);
                DrawHUD(pHUD);
                DrawMemory();
            }
        }
    }

    auto fnc = pFunc->GetFullName();
    if (Cheat::localPlayer && Cheat::localController && Cheat::Memory::ShowDamage && fnc.find("ClientOnDamageToOther") != std::string::npos) 
    {
        auto localContrller = reinterpret_cast<ASTExtraPlayerController*>(pObj);
        auto Params = reinterpret_cast<ASTExtraPlayerController_ClientOnDamageToOther_Params*>(pArgs);
        if (Params) 
        {
            float damage = Params->_DamageToOther;
            if (auto HUD = reinterpret_cast<ASurviveHUD*>(localContrller->MyHUD)) 
            {
                HUD->AddHitDamageNumberWithConfig(damage, Cheat::localPlayer, Cheat::localController, 0, 1, 1, 1);
            }
        }
    }
    return oProcessEvent(pObj, pFunc, pArgs);
}

void initOffset() 
{
    ProcessEvent = (Cheat::libUE4Base + 0x8BE9D08);
    if (ProcessEvent) 
    {
       shadowhook_init(shadowhook_mode_t::SHADOWHOOK_MODE_UNIQUE, 0);
       shadowhook_hook_func_addr((void *)(Cheat::libUE4Base + 0x8BE9D08), (void *)hkProcessEvent, (void **)&oProcessEvent);
       
    }
}

*/


void FixGameCrash()
{
    // Disabled: previously deleted private files and obstructed crash reporters.
    // Original implementation remains in Git history; no replacement suppression.
    KennyDiagnostics::Once(22,KennyDiagnostics::Severity::Info,0,true,"Destructive startup deletion/crash-report suppression disabled");
}


void *RunGame(void *) 
{
    KennyDiagnostics::Once(3,KennyDiagnostics::Severity::Info,0,true,"Startup thread running");
    while(!NativeGlobalsReady.load(std::memory_order_acquire))usleep(1000);
    KennyDiagnostics::Once(26,KennyDiagnostics::Severity::Info,0,true,"Translation-unit C++ globals initialized");
    FixGameCrash();
    KennyDiagnostics::Once(23,KennyDiagnostics::Severity::Info,0,true,"Waiting for original native runtime");

    Cheat::libUE4Base = Tools::GetBaseAddress("libUE4.so");

    while (!Cheat::libUE4Base) 
    {
        Cheat::libUE4Base = Tools::GetBaseAddress("libUE4.so");
        sleep(1);
    }

    while (!g_App) 
    {
        g_App = *(android_app **)(Cheat::libUE4Base + Cheat::GNativeAndroidApp_Offset);
        sleep(1);
    }

    PresentationApp.store(g_App,std::memory_order_release);
    KennyDiagnostics::Once(24,KennyDiagnostics::Severity::Info,0,true,"Original application context discovered");
    if(g_App->activity&&g_App->activity->internalDataPath){
        const bool stored=KennyDiagnostics::SetStorage(g_App->activity->internalDataPath);
        KennyDiagnostics::Once(27,stored?KennyDiagnostics::Severity::Info:KennyDiagnostics::Severity::Warning,stored?0:errno,stored,"App-private diagnostic storage initialization");
    }
    KennyDiagnostics::Once(25,KennyDiagnostics::Severity::Info,0,true,"Waiting for original SDK globals");
    FName::GNames = GetGNames();

    while (!FName::GNames) 
    {
        FName::GNames = GetGNames();
        sleep(1);
    }

    UObject::GUObjectArray = (FUObjectArray *)(Cheat::libUE4Base + Cheat::GUObject_Offset);
    
    KennyDiagnostics::Once(36,KennyDiagnostics::Severity::Info,0,true,"Existing native integration registration starting");
    const int hookInit=shadowhook_init(shadowhook_mode_t::SHADOWHOOK_MODE_UNIQUE, 0);
    KennyDiagnostics::Event(36,hookInit==0?KennyDiagnostics::Severity::Info:KennyDiagnostics::Severity::Warning,hookInit,hookInit==0,"Existing hook library initialization result");
    
    shadowhook_hook_func_addr((void *)(Cheat::libUE4Base + 0xAD5866C), (void *)hkReceiveDrawHUD, (void **)&oReceiveDrawHUD);
  
    shadowhook_hook_func_addr((void *)(Cheat::libUE4Base + 0xCC8F5E0), (void *)_eglSwapBuffers, (void **)&orig_eglSwapBuffers);
  
    //shadowhook_hook_sym_name("/system/lib64/libEGL.so", "eglSwapBuffers", (void *)_eglSwapBuffers, (void **)&orig_eglSwapBuffers);
    
    shadowhook_hook_func_addr((void *)(Cheat::libUE4Base + 0x6DAB6CC), (void *)xShootBulletInner, (void **)&ShootBulletInner);
    
    
    shadowhook_hook_sym_name("libandroid.so", "AInputQueue_getEvent",
        (void*)_HAI, (void**)&orig_AInputQueue_getEvent);

    if (_SDK() < 35) {
        shadowhook_hook_sym_name("libinput.so",
            "_ZN7android13InputConsumer21initializeMotionEventEPNS_11MotionEventEPKNS_12InputMessageE",
            (void*)_OI, (void**)&orig_onInputEvent);
    }
    if (_SDK() == 35) {
        shadowhook_hook_sym_name("libinput.so",
            "_ZN7android11MotionEvent8copyFromEPKS0_b",
            (void*)_OI, (void**)&orig_onInputEvent);
    }
    if (_SDK() == 36) {
        shadowhook_hook_sym_name("libinput.so",
            "_ZN7android11MotionEvent8copyFromEPKS0_b",
            (void*)_OI, (void**)&orig_onInputEvent);
    }

    shadowhook_hook_sym_name("libandroid.so", "ANativeWindow_getWidth",
        (void*)_ANativeWindow_getWidth, (void**)&orig_ANativeWindow_getWidth);
    shadowhook_hook_sym_name("libandroid.so", "ANativeWindow_getHeight",
        (void*)_ANativeWindow_getHeight, (void**)&orig_ANativeWindow_getHeight);
	
	//initOffset();
	KennyDiagnostics::Once(37,KennyDiagnostics::Severity::Info,0,true,"Existing integration registration reached; original Lua initialization next");
	InitLuaHooks(Cheat::libUE4Base);
    KennyDiagnostics::Once(38,KennyDiagnostics::Severity::Info,0,true,"Original Lua initialization returned; existing item parse next");
    items_data = json::parse(JSON_ITEMS);
    AutoEspOn();
    KennyDiagnostics::Once(39,KennyDiagnostics::Severity::Info,0,true,"Original startup configuration completed");
    return nullptr;
}

__attribute__ ((constructor))
void _init()
{
    KennyDiagnostics::Once(1,KennyDiagnostics::Severity::Info,0,true,"Native constructor entered; build=" KPH_BUILD_ID);
    const int result=pthread_create(&t,nullptr,RunGame,nullptr);
    KennyDiagnostics::Once(2,result==0?KennyDiagnostics::Severity::Info:KennyDiagnostics::Severity::Error,result,result==0,"Startup thread creation");
    if(result==0)pthread_detach(t);
}
// Explicitly release the worker only after this translation unit's dynamic
// globals (JSON, maps, strings and existing configuration) have been initialized.
struct NativeGlobalsBarrier {NativeGlobalsBarrier(){NativeGlobalsReady.store(true,std::memory_order_release);}};
static NativeGlobalsBarrier nativeGlobalsBarrier;
