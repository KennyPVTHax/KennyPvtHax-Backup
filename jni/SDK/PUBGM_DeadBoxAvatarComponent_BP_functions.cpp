// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Functions
//---------------------By BangJO---------------------------

// Function DeadBoxAvatarComponent_BP.DeadBoxAvatarComponent_BP_C.GetVehicleDiedPath
// (Public, HasOutParms, BlueprintCallable, BlueprintEvent, BlueprintPure, Const)
// Parameters:
// int ItemId (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FString Path (Parm, OutParm, ZeroConstructor)

void UDeadBoxAvatarComponent_BP_C::GetVehicleDiedPath(int ItemId, struct FString* Path)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function DeadBoxAvatarComponent_BP.DeadBoxAvatarComponent_BP_C.GetVehicleDiedPath");

	UDeadBoxAvatarComponent_BP_C_GetVehicleDiedPath_Params params;
	params.ItemId = ItemId;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	if (Path != nullptr)
		*Path = params.Path;
}


// Function DeadBoxAvatarComponent_BP.DeadBoxAvatarComponent_BP_C.IsVehicleAvatarID
// (Public, HasOutParms, BlueprintCallable, BlueprintEvent, BlueprintPure, Const)
// Parameters:
// int ItemId (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool IsVehicleAvatarID (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UDeadBoxAvatarComponent_BP_C::IsVehicleAvatarID(int ItemId, bool* IsVehicleAvatarID)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function DeadBoxAvatarComponent_BP.DeadBoxAvatarComponent_BP_C.IsVehicleAvatarID");

	UDeadBoxAvatarComponent_BP_C_IsVehicleAvatarID_Params params;
	params.ItemId = ItemId;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	if (IsVehicleAvatarID != nullptr)
		*IsVehicleAvatarID = params.IsVehicleAvatarID;
}


// Function DeadBoxAvatarComponent_BP.DeadBoxAvatarComponent_BP_C.GetItemAvatarHandlePath
// (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent, Const)
// Parameters:
// int* ItemId (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FString ReturnValue (Parm, OutParm, ZeroConstructor, ReturnParm)

struct FString UDeadBoxAvatarComponent_BP_C::GetItemAvatarHandlePath(int* ItemId)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function DeadBoxAvatarComponent_BP.DeadBoxAvatarComponent_BP_C.GetItemAvatarHandlePath");

	UDeadBoxAvatarComponent_BP_C_GetItemAvatarHandlePath_Params params;
	params.ItemId = ItemId;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function DeadBoxAvatarComponent_BP.DeadBoxAvatarComponent_BP_C.GetItemAvatarHandle
// (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent)
// Parameters:
// int* ItemId (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UBackpackCommonAvatarHandle* ReturnValue (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UBackpackCommonAvatarHandle* UDeadBoxAvatarComponent_BP_C::GetItemAvatarHandle(int* ItemId)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function DeadBoxAvatarComponent_BP.DeadBoxAvatarComponent_BP_C.GetItemAvatarHandle");

	UDeadBoxAvatarComponent_BP_C_GetItemAvatarHandle_Params params;
	params.ItemId = ItemId;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	return params.ReturnValue;
}


}

