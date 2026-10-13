#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Parameters
//---------------------By BangJO---------------------------

// Function BP_LobbyVehicle.BP_LobbyVehicle_C.TrySetHighLight
struct ABP_LobbyVehicle_C_TrySetHighLight_Params
{
	float NewParam; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float NewParam1; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float NewParam2; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_LobbyVehicle.BP_LobbyVehicle_C.SetHighLight
struct ABP_LobbyVehicle_C_SetHighLight_Params
{
	float invincible; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float FreExp; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float Speed; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_LobbyVehicle.BP_LobbyVehicle_C.SetDMIParam
struct ABP_LobbyVehicle_C_SetDMIParam_Params
{
	class UMaterialInstanceDynamic* Target; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FName Name; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float Value; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_LobbyVehicle.BP_LobbyVehicle_C.GetVehicleMasterPath
struct ABP_LobbyVehicle_C_GetVehicleMasterPath_Params
{
	int VehicleSkinID; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FString MeshBasePath; // (Parm, OutParm, ZeroConstructor)
};

// Function BP_LobbyVehicle.BP_LobbyVehicle_C.UserConstructionScript
struct ABP_LobbyVehicle_C_UserConstructionScript_Params
{
};

}

