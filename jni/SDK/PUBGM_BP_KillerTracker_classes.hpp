#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass BP_KillerTracker.BP_KillerTracker_C
// 0x0018 (0x0568 - 0x0550)
class ABP_KillerTracker_C : public AKillerTracker
{
public:
	class UCameraComponent* Camera; // 0x0550(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class USpringArmComponent* SpringArm; // 0x0558(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class USceneComponent* DefaultSceneRoot; // 0x0560(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass BP_KillerTracker.BP_KillerTracker_C");
		return pStaticClass;
	}


	void UserConstructionScript();
};


}

