#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass Bp_MInitv_RandomEvent_Trigger.Bp_MInitv_RandomEvent_Trigger_C
// 0x0018 (0x04C8 - 0x04B0)
class ABp_MInitv_RandomEvent_Trigger_C : public AActor
{
public:
	class UBoxComponent* Box; // 0x04B0(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FString EventName; // 0x04B8(0x0010) (Edit, BlueprintVisible, ZeroConstructor)

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass Bp_MInitv_RandomEvent_Trigger.Bp_MInitv_RandomEvent_Trigger_C");
		return pStaticClass;
	}


	void UserConstructionScript();
};


}

