// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Functions
//---------------------By BangJO---------------------------

// Function Bp_MInitv_RandomEvent_Trigger.Bp_MInitv_RandomEvent_Trigger_C.UserConstructionScript
// (Event, Public, BlueprintCallable, BlueprintEvent)

void ABp_MInitv_RandomEvent_Trigger_C::UserConstructionScript()
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Bp_MInitv_RandomEvent_Trigger.Bp_MInitv_RandomEvent_Trigger_C.UserConstructionScript");

	ABp_MInitv_RandomEvent_Trigger_C_UserConstructionScript_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


}

