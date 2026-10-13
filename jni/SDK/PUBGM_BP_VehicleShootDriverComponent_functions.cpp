// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Functions
//---------------------By BangJO---------------------------

// Function BP_VehicleShootDriverComponent.BP_VehicleShootDriverComponent_C.ReceiveBeginPlay
// (Event, Public, BlueprintEvent)

void UBP_VehicleShootDriverComponent_C::ReceiveBeginPlay()
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function BP_VehicleShootDriverComponent.BP_VehicleShootDriverComponent_C.ReceiveBeginPlay");

	UBP_VehicleShootDriverComponent_C_ReceiveBeginPlay_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function BP_VehicleShootDriverComponent.BP_VehicleShootDriverComponent_C.ReceiveEndPlay
// (Event, Public, BlueprintEvent)
// Parameters:
// TEnumAsByte<enum EEndPlayReason>* EndPlayReason (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_VehicleShootDriverComponent_C::ReceiveEndPlay(TEnumAsByte<enum EEndPlayReason>* EndPlayReason)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function BP_VehicleShootDriverComponent.BP_VehicleShootDriverComponent_C.ReceiveEndPlay");

	UBP_VehicleShootDriverComponent_C_ReceiveEndPlay_Params params;
	params.EndPlayReason = EndPlayReason;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function BP_VehicleShootDriverComponent.BP_VehicleShootDriverComponent_C.ExecuteUbergraph_BP_VehicleShootDriverComponent
// ()
// Parameters:
// int EntryPoint (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_VehicleShootDriverComponent_C::ExecuteUbergraph_BP_VehicleShootDriverComponent(int EntryPoint)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function BP_VehicleShootDriverComponent.BP_VehicleShootDriverComponent_C.ExecuteUbergraph_BP_VehicleShootDriverComponent");

	UBP_VehicleShootDriverComponent_C_ExecuteUbergraph_BP_VehicleShootDriverComponent_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


}

