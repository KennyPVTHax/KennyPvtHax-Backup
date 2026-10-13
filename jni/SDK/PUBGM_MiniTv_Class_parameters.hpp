#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Parameters
//---------------------By BangJO---------------------------

// Function MiniTv_Class.MiniTv_Class_C.DestoryPhoneMesh
struct AMiniTv_Class_C_DestoryPhoneMesh_Params
{
};

// Function MiniTv_Class.MiniTv_Class_C.PlayPhoneAnim
struct AMiniTv_Class_C_PlayPhoneAnim_Params
{
};

// Function MiniTv_Class.MiniTv_Class_C.TouchEnd
struct AMiniTv_Class_C_TouchEnd_Params
{
	TEnumAsByte<enum ETouchIndex> Finger; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function MiniTv_Class.MiniTv_Class_C.TouchStart
struct AMiniTv_Class_C_TouchStart_Params
{
	TEnumAsByte<enum ETouchIndex> Finger; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function MiniTv_Class.MiniTv_Class_C.UserConstructionScript
struct AMiniTv_Class_C_UserConstructionScript_Params
{
};

// Function MiniTv_Class.MiniTv_Class_C.BndEvt__SkeletalMesh_K2Node_ComponentBoundEvent_0_ComponentOnInputTouchBeginSignature__DelegateSignature
struct AMiniTv_Class_C_BndEvt__SkeletalMesh_K2Node_ComponentBoundEvent_0_ComponentOnInputTouchBeginSignature__DelegateSignature_Params
{
	TEnumAsByte<enum ETouchIndex> FingerIndex; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UPrimitiveComponent* TouchedComponent; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function MiniTv_Class.MiniTv_Class_C.BndEvt__SkeletalMesh_K2Node_ComponentBoundEvent_1_ComponentOnInputTouchEndSignature__DelegateSignature
struct AMiniTv_Class_C_BndEvt__SkeletalMesh_K2Node_ComponentBoundEvent_1_ComponentOnInputTouchEndSignature__DelegateSignature_Params
{
	TEnumAsByte<enum ETouchIndex> FingerIndex; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UPrimitiveComponent* TouchedComponent; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function MiniTv_Class.MiniTv_Class_C.ReceiveTick
struct AMiniTv_Class_C_ReceiveTick_Params
{
	float* DeltaSeconds; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function MiniTv_Class.MiniTv_Class_C.ExecuteUbergraph_MiniTv_Class
struct AMiniTv_Class_C_ExecuteUbergraph_MiniTv_Class_Params
{
	int EntryPoint; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

