// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Functions
//---------------------By BangJO---------------------------

// Function PetSpecifiedAnim.PetSpecifiedAnim_C.ReceiveExecuteAI
// (Event, Protected, BlueprintEvent)
// Parameters:
// class AAIController** OwnerController (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class APawn** ControlledPawn (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UPetSpecifiedAnim_C::ReceiveExecuteAI(class AAIController** OwnerController, class APawn** ControlledPawn)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PetSpecifiedAnim.PetSpecifiedAnim_C.ReceiveExecuteAI");

	UPetSpecifiedAnim_C_ReceiveExecuteAI_Params params;
	params.OwnerController = OwnerController;
	params.ControlledPawn = ControlledPawn;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PetSpecifiedAnim.PetSpecifiedAnim_C.ExecuteUbergraph_PetSpecifiedAnim
// (HasDefaults)
// Parameters:
// int EntryPoint (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UPetSpecifiedAnim_C::ExecuteUbergraph_PetSpecifiedAnim(int EntryPoint)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PetSpecifiedAnim.PetSpecifiedAnim_C.ExecuteUbergraph_PetSpecifiedAnim");

	UPetSpecifiedAnim_C_ExecuteUbergraph_PetSpecifiedAnim_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


}

