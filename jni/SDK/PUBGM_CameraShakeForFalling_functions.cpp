// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Functions
//---------------------By BangJO---------------------------

// Function CameraShakeForFalling.CameraShakeForFalling_C.ReceivePlayShake
// (Event, Public, BlueprintEvent)
// Parameters:
// float* Scale (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UCameraShakeForFalling_C::ReceivePlayShake(float* Scale)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function CameraShakeForFalling.CameraShakeForFalling_C.ReceivePlayShake");

	UCameraShakeForFalling_C_ReceivePlayShake_Params params;
	params.Scale = Scale;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function CameraShakeForFalling.CameraShakeForFalling_C.ExecuteUbergraph_CameraShakeForFalling
// ()
// Parameters:
// int EntryPoint (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UCameraShakeForFalling_C::ExecuteUbergraph_CameraShakeForFalling(int EntryPoint)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function CameraShakeForFalling.CameraShakeForFalling_C.ExecuteUbergraph_CameraShakeForFalling");

	UCameraShakeForFalling_C_ExecuteUbergraph_CameraShakeForFalling_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


}

