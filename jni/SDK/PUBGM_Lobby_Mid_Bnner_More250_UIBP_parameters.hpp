#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Parameters
//---------------------By BangJO---------------------------

// Function Lobby_Mid_Bnner_More250_UIBP.Lobby_Mid_Bnner_More250_UIBP_C.GetCurScroll
struct ULobby_Mid_Bnner_More250_UIBP_C_GetCurScroll_Params
{
	class ULoopScrollBox* Scroll; // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Lobby_Mid_Bnner_More250_UIBP.Lobby_Mid_Bnner_More250_UIBP_C.GetOffset
struct ULobby_Mid_Bnner_More250_UIBP_C_GetOffset_Params
{
	float Offset; // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Lobby_Mid_Bnner_More250_UIBP.Lobby_Mid_Bnner_More250_UIBP_C.GetCurrentIndex
struct ULobby_Mid_Bnner_More250_UIBP_C_GetCurrentIndex_Params
{
	int Index; // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Lobby_Mid_Bnner_More250_UIBP.Lobby_Mid_Bnner_More250_UIBP_C.OnClickActivityItem
struct ULobby_Mid_Bnner_More250_UIBP_C_OnClickActivityItem_Params
{
	class ULobby_Activity_BtnItem_C* Item; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Lobby_Mid_Bnner_More250_UIBP.Lobby_Mid_Bnner_More250_UIBP_C.UpdateCurrentPage
struct ULobby_Mid_Bnner_More250_UIBP_C_UpdateCurrentPage_Params
{
};

// Function Lobby_Mid_Bnner_More250_UIBP.Lobby_Mid_Bnner_More250_UIBP_C.SetActivityListPageCount
struct ULobby_Mid_Bnner_More250_UIBP_C_SetActivityListPageCount_Params
{
	int pageCount; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Lobby_Mid_Bnner_More250_UIBP.Lobby_Mid_Bnner_More250_UIBP_C.Tick
struct ULobby_Mid_Bnner_More250_UIBP_C_Tick_Params
{
	struct FGeometry* MyGeometry; // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float* InDeltaTime; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Lobby_Mid_Bnner_More250_UIBP.Lobby_Mid_Bnner_More250_UIBP_C.ExecuteUbergraph_Lobby_Mid_Bnner_More250_UIBP
struct ULobby_Mid_Bnner_More250_UIBP_C_ExecuteUbergraph_Lobby_Mid_Bnner_More250_UIBP_Params
{
	int EntryPoint; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Lobby_Mid_Bnner_More250_UIBP.Lobby_Mid_Bnner_More250_UIBP_C.EventDispatcherClickItem__DelegateSignature
struct ULobby_Mid_Bnner_More250_UIBP_C_EventDispatcherClickItem__DelegateSignature_Params
{
	int ID; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FString JumpUrl; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
};

}

