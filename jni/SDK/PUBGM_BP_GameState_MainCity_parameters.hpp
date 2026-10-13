#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Parameters
//---------------------By BangJO---------------------------

// Function BP_GameState_MainCity.BP_GameState_MainCity_C.MulticastRPC_SwitchDS
struct ABP_GameState_MainCity_C_MulticastRPC_SwitchDS_Params
{
	uint64_t MulticastRPC_SwitchDS_param1; // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_GameState_MainCity.BP_GameState_MainCity_C.MultiCast_GenericRPC
struct ABP_GameState_MainCity_C_MultiCast_GenericRPC_Params
{
	int MultiCast_GenericRPC_param1; // (Parm, ZeroConstructor, IsPlainOldData)
	class UObject* MultiCast_GenericRPC_param2; // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<unsigned char> MultiCast_GenericRPC_param3; // (Parm, ZeroConstructor)
};

// Function BP_GameState_MainCity.BP_GameState_MainCity_C.#[FeatureRPC(ReviveState.MulticastRevivalTimeEnd)]
struct ABP_GameState_MainCity_C___FeatureRPC_ReviveState_MulticastRevivalTimeEnd___Params
{
};

// Function BP_GameState_MainCity.BP_GameState_MainCity_C.#[FeatureRPC(FatalDamageFeature.MulticastRPC_BroadcastFatalDamageToClientForLua)]
struct ABP_GameState_MainCity_C___FeatureRPC_FatalDamageFeature_MulticastRPC_BroadcastFatalDamageToClientForLua___Params
{
	struct FFatalDamageParameterCompress __FeatureRPC_FatalDamageFeature_MulticastRPC_BroadcastFatalDamageToClientForLua___param1; // (Parm)
	TArray<unsigned char> __FeatureRPC_FatalDamageFeature_MulticastRPC_BroadcastFatalDamageToClientForLua___param2; // (Parm, ZeroConstructor)
};

// Function BP_GameState_MainCity.BP_GameState_MainCity_C.UserConstructionScript
struct ABP_GameState_MainCity_C_UserConstructionScript_Params
{
};

}

