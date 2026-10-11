#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Parameters
//---------------------By BangJO---------------------------

// Function BP_AutoAimingComponent.BP_AutoAimingComponent_C.CheckInAngle
struct UBP_AutoAimingComponent_C_CheckInAngle_Params
{
	class AActor** EnemeyActor; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float* MaxAngle; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool ReturnValue; // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_AutoAimingComponent.BP_AutoAimingComponent_C.CheckSmoke
struct UBP_AutoAimingComponent_C_CheckSmoke_Params
{
	struct FVector StartPoint; // (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, IsPlainOldData)
	struct FVector EndPoint; // (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, IsPlainOldData)
	class AActor** EnemeyActor; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool ReturnValue; // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_AutoAimingComponent.BP_AutoAimingComponent_C.CanEnemeyRaycastReach
struct UBP_AutoAimingComponent_C_CanEnemeyRaycastReach_Params
{
	struct FVector StartPoint; // (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, IsPlainOldData)
	struct FVector EndPoint; // (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, IsPlainOldData)
	class AActor** EnemeyActor; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FName OutHitBoneName; // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	bool ReturnValue; // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_AutoAimingComponent.BP_AutoAimingComponent_C.BPDrawDebugInfo
struct UBP_AutoAimingComponent_C_BPDrawDebugInfo_Params
{
	TArray<float>* AutoAimParams; // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ZeroConstructor, ReferenceParm)
};

// Function BP_AutoAimingComponent.BP_AutoAimingComponent_C.ExecuteUbergraph_BP_AutoAimingComponent
struct UBP_AutoAimingComponent_C_ExecuteUbergraph_BP_AutoAimingComponent_Params
{
	int EntryPoint; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

