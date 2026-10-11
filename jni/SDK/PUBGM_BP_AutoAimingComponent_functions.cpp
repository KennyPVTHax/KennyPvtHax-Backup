// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Functions
//---------------------By BangJO---------------------------

// Function BP_AutoAimingComponent.BP_AutoAimingComponent_C.CheckInAngle
// (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
// Parameters:
// class AActor** EnemeyActor (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float* MaxAngle (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool ReturnValue (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UBP_AutoAimingComponent_C::CheckInAngle(class AActor** EnemeyActor, float* MaxAngle)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function BP_AutoAimingComponent.BP_AutoAimingComponent_C.CheckInAngle");

	UBP_AutoAimingComponent_C_CheckInAngle_Params params;
	params.EnemeyActor = EnemeyActor;
	params.MaxAngle = MaxAngle;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_AutoAimingComponent.BP_AutoAimingComponent_C.CheckSmoke
// (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
// Parameters:
// struct FVector StartPoint (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, IsPlainOldData)
// struct FVector EndPoint (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, IsPlainOldData)
// class AActor** EnemeyActor (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool ReturnValue (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UBP_AutoAimingComponent_C::CheckSmoke(class AActor** EnemeyActor, struct FVector* StartPoint, struct FVector* EndPoint)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function BP_AutoAimingComponent.BP_AutoAimingComponent_C.CheckSmoke");

	UBP_AutoAimingComponent_C_CheckSmoke_Params params;
	params.EnemeyActor = EnemeyActor;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	if (StartPoint != nullptr)
		*StartPoint = params.StartPoint;
	if (EndPoint != nullptr)
		*EndPoint = params.EndPoint;

	return params.ReturnValue;
}


// Function BP_AutoAimingComponent.BP_AutoAimingComponent_C.CanEnemeyRaycastReach
// (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
// Parameters:
// struct FVector StartPoint (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, IsPlainOldData)
// struct FVector EndPoint (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, IsPlainOldData)
// class AActor** EnemeyActor (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FName OutHitBoneName (Parm, OutParm, ZeroConstructor, IsPlainOldData)
// bool ReturnValue (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UBP_AutoAimingComponent_C::CanEnemeyRaycastReach(class AActor** EnemeyActor, struct FVector* StartPoint, struct FVector* EndPoint, struct FName* OutHitBoneName)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function BP_AutoAimingComponent.BP_AutoAimingComponent_C.CanEnemeyRaycastReach");

	UBP_AutoAimingComponent_C_CanEnemeyRaycastReach_Params params;
	params.EnemeyActor = EnemeyActor;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	if (StartPoint != nullptr)
		*StartPoint = params.StartPoint;
	if (EndPoint != nullptr)
		*EndPoint = params.EndPoint;
	if (OutHitBoneName != nullptr)
		*OutHitBoneName = params.OutHitBoneName;

	return params.ReturnValue;
}


// Function BP_AutoAimingComponent.BP_AutoAimingComponent_C.BPDrawDebugInfo
// (Event, Public, HasOutParms, BlueprintEvent)
// Parameters:
// TArray<float>* AutoAimParams (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ZeroConstructor, ReferenceParm)

void UBP_AutoAimingComponent_C::BPDrawDebugInfo(TArray<float>* AutoAimParams)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function BP_AutoAimingComponent.BP_AutoAimingComponent_C.BPDrawDebugInfo");

	UBP_AutoAimingComponent_C_BPDrawDebugInfo_Params params;
	params.AutoAimParams = AutoAimParams;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function BP_AutoAimingComponent.BP_AutoAimingComponent_C.ExecuteUbergraph_BP_AutoAimingComponent
// ()
// Parameters:
// int EntryPoint (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_AutoAimingComponent_C::ExecuteUbergraph_BP_AutoAimingComponent(int EntryPoint)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function BP_AutoAimingComponent.BP_AutoAimingComponent_C.ExecuteUbergraph_BP_AutoAimingComponent");

	UBP_AutoAimingComponent_C_ExecuteUbergraph_BP_AutoAimingComponent_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


}

