#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass BP_AutoAimingComponent.BP_AutoAimingComponent_C
// 0x0018 (0x0668 - 0x0650)
class UBP_AutoAimingComponent_C : public UWeaponAutoAimingComponent
{
public:
	struct FPointerToUberGraphFrame UberGraphFrame; // 0x0650(0x0008) (Transient, DuplicateTransient)
	TEnumAsByte<enum EDrawDebugTrace> DrawDebugType; // 0x0658(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char UnknownData00[0x7]; // 0x0659(0x0007) MISSED OFFSET
	class UUserWidget* DebugUI; // 0x0660(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass BP_AutoAimingComponent.BP_AutoAimingComponent_C");
		return pStaticClass;
	}


	bool CheckInAngle(class AActor** EnemeyActor, float* MaxAngle);
	bool CheckSmoke(class AActor** EnemeyActor, struct FVector* StartPoint, struct FVector* EndPoint);
	bool CanEnemeyRaycastReach(class AActor** EnemeyActor, struct FVector* StartPoint, struct FVector* EndPoint, struct FName* OutHitBoneName);
	void BPDrawDebugInfo(TArray<float>* AutoAimParams);
	void ExecuteUbergraph_BP_AutoAimingComponent(int EntryPoint);
};


}

