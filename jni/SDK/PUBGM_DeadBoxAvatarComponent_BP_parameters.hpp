#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Parameters
//---------------------By BangJO---------------------------

// Function DeadBoxAvatarComponent_BP.DeadBoxAvatarComponent_BP_C.GetVehicleDiedPath
struct UDeadBoxAvatarComponent_BP_C_GetVehicleDiedPath_Params
{
	int ItemId; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FString Path; // (Parm, OutParm, ZeroConstructor)
};

// Function DeadBoxAvatarComponent_BP.DeadBoxAvatarComponent_BP_C.IsVehicleAvatarID
struct UDeadBoxAvatarComponent_BP_C_IsVehicleAvatarID_Params
{
	int ItemId; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool IsVehicleAvatarID; // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function DeadBoxAvatarComponent_BP.DeadBoxAvatarComponent_BP_C.GetItemAvatarHandlePath
struct UDeadBoxAvatarComponent_BP_C_GetItemAvatarHandlePath_Params
{
	int* ItemId; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FString ReturnValue; // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function DeadBoxAvatarComponent_BP.DeadBoxAvatarComponent_BP_C.GetItemAvatarHandle
struct UDeadBoxAvatarComponent_BP_C_GetItemAvatarHandle_Params
{
	int* ItemId; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UBackpackCommonAvatarHandle* ReturnValue; // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

}

