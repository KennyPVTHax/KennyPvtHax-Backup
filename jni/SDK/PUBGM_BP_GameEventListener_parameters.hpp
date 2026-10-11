#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Parameters
//---------------------By BangJO---------------------------

// Function BP_GameEventListener.BP_GameEventListener_C.SetDefaultNearClipPlane
struct UBP_GameEventListener_C_SetDefaultNearClipPlane_Params
{
};

// Function BP_GameEventListener.BP_GameEventListener_C.IsIOSPlatform
struct UBP_GameEventListener_C_IsIOSPlatform_Params
{
};

// Function BP_GameEventListener.BP_GameEventListener_C.SetDefaultRendering
struct UBP_GameEventListener_C_SetDefaultRendering_Params
{
};

// Function BP_GameEventListener.BP_GameEventListener_C.EnableGrassLOD
struct UBP_GameEventListener_C_EnableGrassLOD_Params
{
	int Enable; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_GameEventListener.BP_GameEventListener_C.ChangeStreamingLevel
struct UBP_GameEventListener_C_ChangeStreamingLevel_Params
{
};

// Function BP_GameEventListener.BP_GameEventListener_C.InitIncaseReconnect
struct UBP_GameEventListener_C_InitIncaseReconnect_Params
{
};

// Function BP_GameEventListener.BP_GameEventListener_C.ReceiveBeginPlay
struct UBP_GameEventListener_C_ReceiveBeginPlay_Params
{
};

// Function BP_GameEventListener.BP_GameEventListener_C.ReceiveEndPlay
struct UBP_GameEventListener_C_ReceiveEndPlay_Params
{
	TEnumAsByte<enum EEndPlayReason>* EndPlayReason; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_GameEventListener.BP_GameEventListener_C.UnloadTree
struct UBP_GameEventListener_C_UnloadTree_Params
{
};

// Function BP_GameEventListener.BP_GameEventListener_C.LoadTree
struct UBP_GameEventListener_C_LoadTree_Params
{
};

// Function BP_GameEventListener.BP_GameEventListener_C.ExecuteUbergraph_BP_GameEventListener
struct UBP_GameEventListener_C_ExecuteUbergraph_BP_GameEventListener_Params
{
	int EntryPoint; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

