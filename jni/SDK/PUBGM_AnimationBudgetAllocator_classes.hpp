#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// Class AnimationBudgetAllocator.SkeletalMeshComponentBudgeted
// 0x0020 (0x1370 - 0x1350)
class USkeletalMeshComponentBudgeted : public USkeletalMeshComponent
{
public:
	unsigned char UnknownData00[0x18]; // 0x1350(0x0018) MISSED OFFSET
	unsigned char bAutoRegisterWithBudgetAllocator : 1; // 0x1368(0x0001) (Edit, BlueprintVisible)
	unsigned char bAutoCalculateSignificance : 1; // 0x1368(0x0001) (Edit)
	unsigned char bShouldUseActorRenderedFlag : 1; // 0x1368(0x0001) (Edit)
	unsigned char bKeepUpdateRateOptimizationWhenBudgeted : 1; // 0x1368(0x0001) (Edit)
	unsigned char UnknownData01[0x7]; // 0x1369(0x0007) MISSED OFFSET

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class AnimationBudgetAllocator.SkeletalMeshComponentBudgeted");
		return pStaticClass;
	}


	void SetAutoRegisterWithBudgetAllocator(bool bInAutoRegisterWithBudgetAllocator);
};


// Class AnimationBudgetAllocator.AnimationBudgetBlueprintLibrary
// 0x0000 (0x0028 - 0x0028)
class UAnimationBudgetBlueprintLibrary : public UBlueprintFunctionLibrary
{
public:

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class AnimationBudgetAllocator.AnimationBudgetBlueprintLibrary");
		return pStaticClass;
	}


	static void SetAnimationBudgetParameters(class UObject* WorldContextObject, const struct FAnimationBudgetAllocatorParameters& InParameters);
	static void EnableAnimationBudget(class UObject* WorldContextObject, bool bEnabled);
};


}

