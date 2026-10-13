#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass BP_BattleRoyaleHUD.BP_BattleRoyaleHUD_C
// 0x0030 (0x08D8 - 0x08A8)
class ABP_BattleRoyaleHUD_C : public ASurviveHUD
{
public:
	struct FPointerToUberGraphFrame UberGraphFrame; // 0x08A8(0x0008) (Transient, DuplicateTransient)
	class USceneComponent* DefaultSceneRoot; // 0x08B0(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	TArray<int> DamageNumberDamageTypes; // 0x08B8(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	TArray<TEnumAsByte<enum EWeaponTypeNew>> InvalidDamageNumberWeaponTypes; // 0x08C8(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass BP_BattleRoyaleHUD.BP_BattleRoyaleHUD_C");
		return pStaticClass;
	}


	bool IsValidDamageNumber(class AActor** DamageCauser, int* DamageTypeId);
	struct FLinearColor GetPlayerNameColorByTeamID(int* TeamID);
	struct FLinearColor GetColorByTeamID(int* TeamID);
	void UserConstructionScript();
	void ReceiveBeginPlay();
	void HitFeedBackChanged(bool BoolValue);
	void OBSHitFeedbackChanged(bool BoolValue);
	void ExecuteUbergraph_BP_BattleRoyaleHUD(int EntryPoint);
};


}

