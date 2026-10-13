#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Parameters
//---------------------By BangJO---------------------------

// Function BasePetController_BP.BasePetController_BP_C.LoadBehaviorTree
struct ABasePetController_BP_C_LoadBehaviorTree_Params
{
	int Clothes; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BasePetController_BP.BasePetController_BP_C.CalcInAirAttackArea
struct ABasePetController_BP_C_CalcInAirAttackArea_Params
{
};

// Function BasePetController_BP.BasePetController_BP_C.OnPlayerStopEmote
struct ABasePetController_BP_C_OnPlayerStopEmote_Params
{
	int EmoteId; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int Reason; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BasePetController_BP.BasePetController_BP_C.OnPlayerPlayEmote
struct ABasePetController_BP_C_OnPlayerPlayEmote_Params
{
	int Emote; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BasePetController_BP.BasePetController_BP_C.UserConstructionScript
struct ABasePetController_BP_C_UserConstructionScript_Params
{
};

// Function BasePetController_BP.BasePetController_BP_C.ReceiveBeginPlay
struct ABasePetController_BP_C_ReceiveBeginPlay_Params
{
};

// Function BasePetController_BP.BasePetController_BP_C.ReceiveEndPlay
struct ABasePetController_BP_C_ReceiveEndPlay_Params
{
	TEnumAsByte<enum EEndPlayReason>* EndPlayReason; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BasePetController_BP.BasePetController_BP_C.ExecuteUbergraph_BasePetController_BP
struct ABasePetController_BP_C_ExecuteUbergraph_BasePetController_BP_Params
{
	int EntryPoint; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

