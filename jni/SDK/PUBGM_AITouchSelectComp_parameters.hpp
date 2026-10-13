#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Parameters
//---------------------By BangJO---------------------------

// Function AITouchSelectComp.AITouchSelectComp_C.UpdateViewportLocalSize
struct UAITouchSelectComp_C_UpdateViewportLocalSize_Params
{
};

// Function AITouchSelectComp.AITouchSelectComp_C.ModifyTouchLoc
struct UAITouchSelectComp_C_ModifyTouchLoc_Params
{
	struct FGeometry MyGeometry; // (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, IsPlainOldData)
	struct FVector2D TouchLoc; // (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, IsPlainOldData)
	struct FVector2D ReturnValue; // (Parm, OutParm, ReturnParm, IsPlainOldData)
};

// Function AITouchSelectComp.AITouchSelectComp_C.ReceiveBeginPlay
struct UAITouchSelectComp_C_ReceiveBeginPlay_Params
{
};

// Function AITouchSelectComp.AITouchSelectComp_C.OnTouchSelect
struct UAITouchSelectComp_C_OnTouchSelect_Params
{
	class AActor* SelectActor; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FVector2D TouchLoc; // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, IsPlainOldData)
};

// Function AITouchSelectComp.AITouchSelectComp_C.OnViewPortChange
struct UAITouchSelectComp_C_OnViewPortChange_Params
{
	struct FVector2D OldViewportSize; // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FVector2D NewViewportSize; // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
};

// Function AITouchSelectComp.AITouchSelectComp_C.ExecuteUbergraph_AITouchSelectComp
struct UAITouchSelectComp_C_ExecuteUbergraph_AITouchSelectComp_Params
{
	int EntryPoint; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

