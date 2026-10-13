#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Parameters
//---------------------By BangJO---------------------------

// Function BP_TouchSelectComponent.BP_TouchSelectComponent_C.RefreshViewportSize
struct UBP_TouchSelectComponent_C_RefreshViewportSize_Params
{
	struct FVector2D OldSize; // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FVector2D NewSize; // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
};

// Function BP_TouchSelectComponent.BP_TouchSelectComponent_C.ModifyTouchLoc
struct UBP_TouchSelectComponent_C_ModifyTouchLoc_Params
{
	struct FGeometry MyGeometry; // (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, IsPlainOldData)
	struct FVector2D TouchLoc; // (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, IsPlainOldData)
	struct FVector2D ReturnValue; // (Parm, OutParm, ReturnParm, IsPlainOldData)
};

// Function BP_TouchSelectComponent.BP_TouchSelectComponent_C.ReceiveBeginPlay
struct UBP_TouchSelectComponent_C_ReceiveBeginPlay_Params
{
};

// Function BP_TouchSelectComponent.BP_TouchSelectComponent_C.ExecuteUbergraph_BP_TouchSelectComponent
struct UBP_TouchSelectComponent_C_ExecuteUbergraph_BP_TouchSelectComponent_Params
{
	int EntryPoint; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

