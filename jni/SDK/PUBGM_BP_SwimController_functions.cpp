// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Functions
//---------------------By BangJO---------------------------

// Function BP_SwimController.BP_SwimController_C.EnterWater_BluePrint
// (Event, Public, BlueprintEvent)

void UBP_SwimController_C::EnterWater_BluePrint()
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function BP_SwimController.BP_SwimController_C.EnterWater_BluePrint");

	UBP_SwimController_C_EnterWater_BluePrint_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function BP_SwimController.BP_SwimController_C.BP_UnderWaterStateChanged
// (Event, Public, BlueprintEvent)
// Parameters:
// bool* bEnterWater (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_SwimController_C::BP_UnderWaterStateChanged(bool* bEnterWater)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function BP_SwimController.BP_SwimController_C.BP_UnderWaterStateChanged");

	UBP_SwimController_C_BP_UnderWaterStateChanged_Params params;
	params.bEnterWater = bEnterWater;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function BP_SwimController.BP_SwimController_C.ExecuteUbergraph_BP_SwimController
// (HasDefaults)
// Parameters:
// int EntryPoint (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_SwimController_C::ExecuteUbergraph_BP_SwimController(int EntryPoint)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function BP_SwimController.BP_SwimController_C.ExecuteUbergraph_BP_SwimController");

	UBP_SwimController_C_ExecuteUbergraph_BP_SwimController_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


}

