// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Functions
//---------------------By BangJO---------------------------

// Function BP_LobbyRefitCloseUp.BP_LobbyRefitCloseUp_C.GetCameraWorldLocation
// (Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
// Parameters:
// struct FVector cameraWorldLocation (Parm, OutParm, IsPlainOldData)

void ABP_LobbyRefitCloseUp_C::GetCameraWorldLocation(struct FVector* cameraWorldLocation)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function BP_LobbyRefitCloseUp.BP_LobbyRefitCloseUp_C.GetCameraWorldLocation");

	ABP_LobbyRefitCloseUp_C_GetCameraWorldLocation_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	if (cameraWorldLocation != nullptr)
		*cameraWorldLocation = params.cameraWorldLocation;
}


// Function BP_LobbyRefitCloseUp.BP_LobbyRefitCloseUp_C.UserConstructionScript
// (Event, Public, BlueprintCallable, BlueprintEvent)

void ABP_LobbyRefitCloseUp_C::UserConstructionScript()
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function BP_LobbyRefitCloseUp.BP_LobbyRefitCloseUp_C.UserConstructionScript");

	ABP_LobbyRefitCloseUp_C_UserConstructionScript_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function BP_LobbyRefitCloseUp.BP_LobbyRefitCloseUp_C.ˆeÙïtè_
// (BlueprintEvent)

void ABP_LobbyRefitCloseUp_C::ˆeÙïtè_()
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function BP_LobbyRefitCloseUp.BP_LobbyRefitCloseUp_C.ˆeÙïtè_");

	ABP_LobbyRefitCloseUp_C_ˆeÙïtè__Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function BP_LobbyRefitCloseUp.BP_LobbyRefitCloseUp_C.ChanTransformWithBlend
// (HasOutParms, BlueprintCallable, BlueprintEvent)
// Parameters:
// struct FTransform B (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, IsPlainOldData)

void ABP_LobbyRefitCloseUp_C::ChanTransformWithBlend(const struct FTransform& B)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function BP_LobbyRefitCloseUp.BP_LobbyRefitCloseUp_C.ChanTransformWithBlend");

	ABP_LobbyRefitCloseUp_C_ChanTransformWithBlend_Params params;
	params.B = B;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function BP_LobbyRefitCloseUp.BP_LobbyRefitCloseUp_C.ExecuteUbergraph_BP_LobbyRefitCloseUp
// (HasDefaults)
// Parameters:
// int EntryPoint (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_LobbyRefitCloseUp_C::ExecuteUbergraph_BP_LobbyRefitCloseUp(int EntryPoint)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function BP_LobbyRefitCloseUp.BP_LobbyRefitCloseUp_C.ExecuteUbergraph_BP_LobbyRefitCloseUp");

	ABP_LobbyRefitCloseUp_C_ExecuteUbergraph_BP_LobbyRefitCloseUp_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


}

