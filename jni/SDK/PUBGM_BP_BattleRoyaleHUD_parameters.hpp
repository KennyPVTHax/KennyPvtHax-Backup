#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Parameters
//---------------------By BangJO---------------------------

// Function BP_BattleRoyaleHUD.BP_BattleRoyaleHUD_C.IsValidDamageNumber
struct ABP_BattleRoyaleHUD_C_IsValidDamageNumber_Params
{
	class AActor** DamageCauser; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int* DamageTypeId; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool ReturnValue; // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_BattleRoyaleHUD.BP_BattleRoyaleHUD_C.GetPlayerNameColorByTeamID
struct ABP_BattleRoyaleHUD_C_GetPlayerNameColorByTeamID_Params
{
	int* TeamID; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FLinearColor ReturnValue; // (Parm, OutParm, ReturnParm, IsPlainOldData)
};

// Function BP_BattleRoyaleHUD.BP_BattleRoyaleHUD_C.GetColorByTeamID
struct ABP_BattleRoyaleHUD_C_GetColorByTeamID_Params
{
	int* TeamID; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FLinearColor ReturnValue; // (Parm, OutParm, ReturnParm, IsPlainOldData)
};

// Function BP_BattleRoyaleHUD.BP_BattleRoyaleHUD_C.UserConstructionScript
struct ABP_BattleRoyaleHUD_C_UserConstructionScript_Params
{
};

// Function BP_BattleRoyaleHUD.BP_BattleRoyaleHUD_C.ReceiveBeginPlay
struct ABP_BattleRoyaleHUD_C_ReceiveBeginPlay_Params
{
};

// Function BP_BattleRoyaleHUD.BP_BattleRoyaleHUD_C.HitFeedBackChanged
struct ABP_BattleRoyaleHUD_C_HitFeedBackChanged_Params
{
	bool BoolValue; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_BattleRoyaleHUD.BP_BattleRoyaleHUD_C.OBSHitFeedbackChanged
struct ABP_BattleRoyaleHUD_C_OBSHitFeedbackChanged_Params
{
	bool BoolValue; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_BattleRoyaleHUD.BP_BattleRoyaleHUD_C.ExecuteUbergraph_BP_BattleRoyaleHUD
struct ABP_BattleRoyaleHUD_C_ExecuteUbergraph_BP_BattleRoyaleHUD_Params
{
	int EntryPoint; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

