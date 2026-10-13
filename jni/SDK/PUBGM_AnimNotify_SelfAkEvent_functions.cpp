// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Functions
//---------------------By BangJO---------------------------

// Function AnimNotify_SelfAkEvent.AnimNotify_SelfAkEvent_C.PlayAkEvent
// (Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent, Const)
// Parameters:
// class USkeletalMeshComponent* MeshComp (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool ReturnValue (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UAnimNotify_SelfAkEvent_C::PlayAkEvent(class USkeletalMeshComponent* MeshComp)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function AnimNotify_SelfAkEvent.AnimNotify_SelfAkEvent_C.PlayAkEvent");

	UAnimNotify_SelfAkEvent_C_PlayAkEvent_Params params;
	params.MeshComp = MeshComp;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function AnimNotify_SelfAkEvent.AnimNotify_SelfAkEvent_C.Received_Notify
// (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent, Const)
// Parameters:
// class USkeletalMeshComponent** MeshComp (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UAnimSequenceBase** Animation (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool ReturnValue (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UAnimNotify_SelfAkEvent_C::Received_Notify(class USkeletalMeshComponent** MeshComp, class UAnimSequenceBase** Animation)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function AnimNotify_SelfAkEvent.AnimNotify_SelfAkEvent_C.Received_Notify");

	UAnimNotify_SelfAkEvent_C_Received_Notify_Params params;
	params.MeshComp = MeshComp;
	params.Animation = Animation;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	return params.ReturnValue;
}


}

