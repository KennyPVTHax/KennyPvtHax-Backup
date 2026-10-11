// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Functions
//---------------------By BangJO---------------------------

// Function BT_BoolValueCheck.BT_BoolValueCheck_C.PerformConditionCheck
// (Event, Protected, HasOutParms, BlueprintCallable, BlueprintEvent)
// Parameters:
// class AActor** OwnerActor (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool ReturnValue (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UBT_BoolValueCheck_C::PerformConditionCheck(class AActor** OwnerActor)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function BT_BoolValueCheck.BT_BoolValueCheck_C.PerformConditionCheck");

	UBT_BoolValueCheck_C_PerformConditionCheck_Params params;
	params.OwnerActor = OwnerActor;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BT_BoolValueCheck.BT_BoolValueCheck_C.ExecuteUbergraph_BT_BoolValueCheck
// ()
// Parameters:
// int EntryPoint (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBT_BoolValueCheck_C::ExecuteUbergraph_BT_BoolValueCheck(int EntryPoint)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function BT_BoolValueCheck.BT_BoolValueCheck_C.ExecuteUbergraph_BT_BoolValueCheck");

	UBT_BoolValueCheck_C_ExecuteUbergraph_BT_BoolValueCheck_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


}

