#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Parameters
//---------------------By BangJO---------------------------

// Function Lobby_Activity250_BtnItem.Lobby_Activity250_BtnItem_C.SetOnlineActivityData
struct ULobby_Activity250_BtnItem_C_SetOnlineActivityData_Params
{
	int status; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FString strText; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
};

// Function Lobby_Activity250_BtnItem.Lobby_Activity250_BtnItem_C.SetBtnData
struct ULobby_Activity250_BtnItem_C_SetBtnData_Params
{
	struct FString ActivityName; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
	struct FString IconPath; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
	struct FString JumpUrl; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
	bool IsShowCountDownIcon; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool IsNew; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FString DependItems; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
	int ActID; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int CreatedUtc; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Lobby_Activity250_BtnItem.Lobby_Activity250_BtnItem_C.ItemClickDispatcher__DelegateSignature
struct ULobby_Activity250_BtnItem_C_ItemClickDispatcher__DelegateSignature_Params
{
	class ULobby_Activity_BtnItem_C* Item; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Lobby_Activity250_BtnItem.Lobby_Activity250_BtnItem_C.ItemMoveRightDispatcher__DelegateSignature
struct ULobby_Activity250_BtnItem_C_ItemMoveRightDispatcher__DelegateSignature_Params
{
	class ULobby_Activity_BtnItem_C* Item; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Lobby_Activity250_BtnItem.Lobby_Activity250_BtnItem_C.ItemMoveLeftDispatcher__DelegateSignature
struct ULobby_Activity250_BtnItem_C_ItemMoveLeftDispatcher__DelegateSignature_Params
{
	class ULobby_Activity_BtnItem_C* Item; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

