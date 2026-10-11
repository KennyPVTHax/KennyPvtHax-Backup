#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Parameters
//---------------------By BangJO---------------------------

// Function Newbie_Banner.Newbie_Banner_C.GetOffset
struct UNewbie_Banner_C_GetOffset_Params
{
	float Offset; // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Newbie_Banner.Newbie_Banner_C.GetCurrentIndex
struct UNewbie_Banner_C_GetCurrentIndex_Params
{
	int Index; // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Newbie_Banner.Newbie_Banner_C.OnClickActivityItem
struct UNewbie_Banner_C_OnClickActivityItem_Params
{
	class ULobby_Activity_BtnItem_C* Item; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Newbie_Banner.Newbie_Banner_C.UpdateCurrentPage
struct UNewbie_Banner_C_UpdateCurrentPage_Params
{
};

// Function Newbie_Banner.Newbie_Banner_C.SetActivityListPageCount
struct UNewbie_Banner_C_SetActivityListPageCount_Params
{
	int pageCount; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Newbie_Banner.Newbie_Banner_C.Tick
struct UNewbie_Banner_C_Tick_Params
{
	struct FGeometry* MyGeometry; // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float* InDeltaTime; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Newbie_Banner.Newbie_Banner_C.ExecuteUbergraph_Newbie_Banner
struct UNewbie_Banner_C_ExecuteUbergraph_Newbie_Banner_Params
{
	int EntryPoint; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Newbie_Banner.Newbie_Banner_C.EventDispatcherClickItem__DelegateSignature
struct UNewbie_Banner_C_EventDispatcherClickItem__DelegateSignature_Params
{
	int ID; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FString JumpUrl; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
};

}

