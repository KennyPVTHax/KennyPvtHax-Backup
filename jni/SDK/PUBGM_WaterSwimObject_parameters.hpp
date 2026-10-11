#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Parameters
//---------------------By BangJO---------------------------

// Function WaterSwimObject.WaterSwimObject_C.SetWaterMaterialByGamePawnEvent
struct AWaterSwimObject_C_SetWaterMaterialByGamePawnEvent_Params
{
	TEnumAsByte<enum EGamePawnEvent> Event; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function WaterSwimObject.WaterSwimObject_C.SetWaterMaterial
struct AWaterSwimObject_C_SetWaterMaterial_Params
{
	int NewParam; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function WaterSwimObject.WaterSwimObject_C.RefreshWaterMaterial
struct AWaterSwimObject_C_RefreshWaterMaterial_Params
{
};

// Function WaterSwimObject.WaterSwimObject_C.DoTrySetWaterMaterial
struct AWaterSwimObject_C_DoTrySetWaterMaterial_Params
{
	int NewParam; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function WaterSwimObject.WaterSwimObject_C.TrySetWaterMaterial
struct AWaterSwimObject_C_TrySetWaterMaterial_Params
{
	int NewParam; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function WaterSwimObject.WaterSwimObject_C.IsSupportIndex
struct AWaterSwimObject_C_IsSupportIndex_Params
{
	int NewParam; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool NewParam1; // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function WaterSwimObject.WaterSwimObject_C.IsNewIphone
struct AWaterSwimObject_C_IsNewIphone_Params
{
	bool IsNewIphone; // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function WaterSwimObject.WaterSwimObject_C.SetWateMaterial
struct AWaterSwimObject_C_SetWateMaterial_Params
{
	bool bHDR; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function WaterSwimObject.WaterSwimObject_C.HideUnderWaterEffect
struct AWaterSwimObject_C_HideUnderWaterEffect_Params
{
	class UStaticMeshComponent* WaterPlane; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UExponentialHeightFogComponent* CamFog; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function WaterSwimObject.WaterSwimObject_C.ShowUnderWaterEffect
struct AWaterSwimObject_C_ShowUnderWaterEffect_Params
{
	class UStaticMeshComponent* WaterPlane; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UExponentialHeightFogComponent* CamFog; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function WaterSwimObject.WaterSwimObject_C.IsCapsult
struct AWaterSwimObject_C_IsCapsult_Params
{
	class UObject* PlayerPawn; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UActorComponent* comp; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool ReturnValue; // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function WaterSwimObject.WaterSwimObject_C.UserConstructionScript
struct AWaterSwimObject_C_UserConstructionScript_Params
{
};

// Function WaterSwimObject.WaterSwimObject_C.BndEvt__PostSceneBox_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature
struct AWaterSwimObject_C_BndEvt__PostSceneBox_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature_Params
{
	class UPrimitiveComponent* OverlappedComponent; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class AActor* OtherActor; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UPrimitiveComponent* OtherComp; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int OtherBodyIndex; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool bFromSweep; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FHitResult SweepResult; // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, IsPlainOldData)
};

// Function WaterSwimObject.WaterSwimObject_C.BndEvt__PostSceneBox_K2Node_ComponentBoundEvent_0_ComponentEndOverlapSignature__DelegateSignature
struct AWaterSwimObject_C_BndEvt__PostSceneBox_K2Node_ComponentBoundEvent_0_ComponentEndOverlapSignature__DelegateSignature_Params
{
	class UPrimitiveComponent* OverlappedComponent; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class AActor* OtherActor; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UPrimitiveComponent* OtherComp; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int OtherBodyIndex; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function WaterSwimObject.WaterSwimObject_C.ReceiveBeginPlay
struct AWaterSwimObject_C_ReceiveBeginPlay_Params
{
};

// Function WaterSwimObject.WaterSwimObject_C.CustomEvent_2
struct AWaterSwimObject_C_CustomEvent_2_Params
{
	int UserQualitySettingLevel; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function WaterSwimObject.WaterSwimObject_C.ReceiveEndPlay
struct AWaterSwimObject_C_ReceiveEndPlay_Params
{
	TEnumAsByte<enum EEndPlayReason>* EndPlayReason; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function WaterSwimObject.WaterSwimObject_C.CustomEvent_3
struct AWaterSwimObject_C_CustomEvent_3_Params
{
	bool UserMsaaSetting; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function WaterSwimObject.WaterSwimObject_C.CustomEvent_4
struct AWaterSwimObject_C_CustomEvent_4_Params
{
	bool bOpenWaterReflection; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function WaterSwimObject.WaterSwimObject_C.ExecuteUbergraph_WaterSwimObject
struct AWaterSwimObject_C_ExecuteUbergraph_WaterSwimObject_Params
{
	int EntryPoint; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

