// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Functions
//---------------------By BangJO---------------------------

// Function BP_ServerSwitcher.BP_ServerSwitcher_C.ReceiveBeginPlay
// (Event, Public, BlueprintEvent)

void UBP_ServerSwitcher_C::ReceiveBeginPlay()
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function BP_ServerSwitcher.BP_ServerSwitcher_C.ReceiveBeginPlay");

	UBP_ServerSwitcher_C_ReceiveBeginPlay_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function BP_ServerSwitcher.BP_ServerSwitcher_C.CustomEvent_1
// (BlueprintCallable, BlueprintEvent)
// Parameters:
// bool BoolValue (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_ServerSwitcher_C::CustomEvent_1(bool BoolValue)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function BP_ServerSwitcher.BP_ServerSwitcher_C.CustomEvent_1");

	UBP_ServerSwitcher_C_CustomEvent_1_Params params;
	params.BoolValue = BoolValue;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function BP_ServerSwitcher.BP_ServerSwitcher_C.ExecuteUbergraph_BP_ServerSwitcher
// ()
// Parameters:
// int EntryPoint (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_ServerSwitcher_C::ExecuteUbergraph_BP_ServerSwitcher(int EntryPoint)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function BP_ServerSwitcher.BP_ServerSwitcher_C.ExecuteUbergraph_BP_ServerSwitcher");

	UBP_ServerSwitcher_C_ExecuteUbergraph_BP_ServerSwitcher_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


}

