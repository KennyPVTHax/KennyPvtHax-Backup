#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass BP_NewFakePlayerAIC.BP_NewFakePlayerAIC_C
// 0x0010 (0x1648 - 0x1638)
class ABP_NewFakePlayerAIC_C : public ANewFakePlayerAIController
{
public:
	class UBP_VehicleAIUserComp_C* BP_VehicleAIUserComp; // 0x1638(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UAIOrderComponent* AIOrder; // 0x1640(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass BP_NewFakePlayerAIC.BP_NewFakePlayerAIC_C");
		return pStaticClass;
	}


	void UserConstructionScript();
};


}

