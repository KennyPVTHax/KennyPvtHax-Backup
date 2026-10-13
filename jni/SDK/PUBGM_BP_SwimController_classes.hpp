#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass BP_SwimController.BP_SwimController_C
// 0x0008 (0x03D0 - 0x03C8)
class UBP_SwimController_C : public UPlayerSwimComponent
{
public:
	struct FPointerToUberGraphFrame UberGraphFrame; // 0x03C8(0x0008) (Transient, DuplicateTransient)

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass BP_SwimController.BP_SwimController_C");
		return pStaticClass;
	}


	void EnterWater_BluePrint();
	void BP_UnderWaterStateChanged(bool* bEnterWater);
	void ExecuteUbergraph_BP_SwimController(int EntryPoint);
};


}

