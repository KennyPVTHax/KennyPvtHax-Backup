// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Functions
//---------------------By BangJO---------------------------

// Function PlayerEventForPet.PlayerEventForPet_C.PlayerStateChange
// (Public, BlueprintCallable, BlueprintEvent)
// Parameters:
// EPawnState State (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// TEnumAsByte<enum EPawnStateChangeType> ChangeType (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UPlayerEventForPet_C::PlayerStateChange(EPawnState State, TEnumAsByte<enum EPawnStateChangeType> ChangeType)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerEventForPet.PlayerEventForPet_C.PlayerStateChange");

	UPlayerEventForPet_C_PlayerStateChange_Params params;
	params.State = State;
	params.ChangeType = ChangeType;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


}

