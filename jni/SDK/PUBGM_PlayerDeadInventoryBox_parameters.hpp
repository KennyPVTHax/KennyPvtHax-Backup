#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Parameters
//---------------------By BangJO---------------------------

// Function PlayerDeadInventoryBox.PlayerDeadInventoryBox_C.LuaCheckCanPlayAudio
struct APlayerDeadInventoryBox_C_LuaCheckCanPlayAudio_Params
{
	bool bCanPlayAudio; // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function PlayerDeadInventoryBox.PlayerDeadInventoryBox_C.GetGroundLocation
struct APlayerDeadInventoryBox_C_GetGroundLocation_Params
{
	struct FVector ReturnValue; // (Parm, OutParm, ReturnParm, IsPlainOldData)
};

// Function PlayerDeadInventoryBox.PlayerDeadInventoryBox_C.GetVector4
struct APlayerDeadInventoryBox_C_GetVector4_Params
{
	struct FVector Dest; // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float Ratio; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function PlayerDeadInventoryBox.PlayerDeadInventoryBox_C.UserConstructionScript
struct APlayerDeadInventoryBox_C_UserConstructionScript_Params
{
};

// Function PlayerDeadInventoryBox.PlayerDeadInventoryBox_C.HideDeadTombApparence
struct APlayerDeadInventoryBox_C_HideDeadTombApparence_Params
{
};

// Function PlayerDeadInventoryBox.PlayerDeadInventoryBox_C.ReceiveTick
struct APlayerDeadInventoryBox_C_ReceiveTick_Params
{
	float* DeltaSeconds; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function PlayerDeadInventoryBox.PlayerDeadInventoryBox_C.SwitchToDeadTombBox
struct APlayerDeadInventoryBox_C_SwitchToDeadTombBox_Params
{
};

// Function PlayerDeadInventoryBox.PlayerDeadInventoryBox_C.ReceiveBeginPlay
struct APlayerDeadInventoryBox_C_ReceiveBeginPlay_Params
{
};

// Function PlayerDeadInventoryBox.PlayerDeadInventoryBox_C.ShowNormal
struct APlayerDeadInventoryBox_C_ShowNormal_Params
{
};

// Function PlayerDeadInventoryBox.PlayerDeadInventoryBox_C.ShowShine
struct APlayerDeadInventoryBox_C_ShowShine_Params
{
};

// Function PlayerDeadInventoryBox.PlayerDeadInventoryBox_C.OpenListenUIEvent
struct APlayerDeadInventoryBox_C_OpenListenUIEvent_Params
{
	bool* bOpen; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function PlayerDeadInventoryBox.PlayerDeadInventoryBox_C.ExecuteUbergraph_PlayerDeadInventoryBox
struct APlayerDeadInventoryBox_C_ExecuteUbergraph_PlayerDeadInventoryBox_Params
{
	int EntryPoint; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

