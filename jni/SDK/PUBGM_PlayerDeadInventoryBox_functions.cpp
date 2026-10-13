// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Functions
//---------------------By BangJO---------------------------

// Function PlayerDeadInventoryBox.PlayerDeadInventoryBox_C.LuaCheckCanPlayAudio
// (Public, HasOutParms, BlueprintCallable, BlueprintEvent)
// Parameters:
// bool bCanPlayAudio (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void APlayerDeadInventoryBox_C::LuaCheckCanPlayAudio(bool* bCanPlayAudio)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerDeadInventoryBox.PlayerDeadInventoryBox_C.LuaCheckCanPlayAudio");

	APlayerDeadInventoryBox_C_LuaCheckCanPlayAudio_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	if (bCanPlayAudio != nullptr)
		*bCanPlayAudio = params.bCanPlayAudio;
}


// Function PlayerDeadInventoryBox.PlayerDeadInventoryBox_C.GetGroundLocation
// (Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
// Parameters:
// struct FVector ReturnValue (Parm, OutParm, ReturnParm, IsPlainOldData)

struct FVector APlayerDeadInventoryBox_C::GetGroundLocation()
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerDeadInventoryBox.PlayerDeadInventoryBox_C.GetGroundLocation");

	APlayerDeadInventoryBox_C_GetGroundLocation_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function PlayerDeadInventoryBox.PlayerDeadInventoryBox_C.GetVector4
// (Public, BlueprintCallable, BlueprintEvent)
// Parameters:
// struct FVector Dest (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float Ratio (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void APlayerDeadInventoryBox_C::GetVector4(const struct FVector& Dest, float Ratio)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerDeadInventoryBox.PlayerDeadInventoryBox_C.GetVector4");

	APlayerDeadInventoryBox_C_GetVector4_Params params;
	params.Dest = Dest;
	params.Ratio = Ratio;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PlayerDeadInventoryBox.PlayerDeadInventoryBox_C.UserConstructionScript
// (Event, Public, BlueprintCallable, BlueprintEvent)

void APlayerDeadInventoryBox_C::UserConstructionScript()
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerDeadInventoryBox.PlayerDeadInventoryBox_C.UserConstructionScript");

	APlayerDeadInventoryBox_C_UserConstructionScript_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PlayerDeadInventoryBox.PlayerDeadInventoryBox_C.HideDeadTombApparence
// (Event, Public, BlueprintCallable, BlueprintEvent)

void APlayerDeadInventoryBox_C::HideDeadTombApparence()
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerDeadInventoryBox.PlayerDeadInventoryBox_C.HideDeadTombApparence");

	APlayerDeadInventoryBox_C_HideDeadTombApparence_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PlayerDeadInventoryBox.PlayerDeadInventoryBox_C.ReceiveTick
// (Event, Public, BlueprintEvent)
// Parameters:
// float* DeltaSeconds (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void APlayerDeadInventoryBox_C::ReceiveTick(float* DeltaSeconds)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerDeadInventoryBox.PlayerDeadInventoryBox_C.ReceiveTick");

	APlayerDeadInventoryBox_C_ReceiveTick_Params params;
	params.DeltaSeconds = DeltaSeconds;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PlayerDeadInventoryBox.PlayerDeadInventoryBox_C.SwitchToDeadTombBox
// (Event, Public, BlueprintCallable, BlueprintEvent)

void APlayerDeadInventoryBox_C::SwitchToDeadTombBox()
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerDeadInventoryBox.PlayerDeadInventoryBox_C.SwitchToDeadTombBox");

	APlayerDeadInventoryBox_C_SwitchToDeadTombBox_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PlayerDeadInventoryBox.PlayerDeadInventoryBox_C.ReceiveBeginPlay
// (Event, Protected, BlueprintEvent)

void APlayerDeadInventoryBox_C::ReceiveBeginPlay()
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerDeadInventoryBox.PlayerDeadInventoryBox_C.ReceiveBeginPlay");

	APlayerDeadInventoryBox_C_ReceiveBeginPlay_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PlayerDeadInventoryBox.PlayerDeadInventoryBox_C.ShowNormal
// (Public, BlueprintCallable, BlueprintEvent)

void APlayerDeadInventoryBox_C::ShowNormal()
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerDeadInventoryBox.PlayerDeadInventoryBox_C.ShowNormal");

	APlayerDeadInventoryBox_C_ShowNormal_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PlayerDeadInventoryBox.PlayerDeadInventoryBox_C.ShowShine
// (Public, BlueprintCallable, BlueprintEvent)

void APlayerDeadInventoryBox_C::ShowShine()
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerDeadInventoryBox.PlayerDeadInventoryBox_C.ShowShine");

	APlayerDeadInventoryBox_C_ShowShine_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PlayerDeadInventoryBox.PlayerDeadInventoryBox_C.OpenListenUIEvent
// (Event, Public, BlueprintCallable, BlueprintEvent)
// Parameters:
// bool* bOpen (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void APlayerDeadInventoryBox_C::OpenListenUIEvent(bool* bOpen)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerDeadInventoryBox.PlayerDeadInventoryBox_C.OpenListenUIEvent");

	APlayerDeadInventoryBox_C_OpenListenUIEvent_Params params;
	params.bOpen = bOpen;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PlayerDeadInventoryBox.PlayerDeadInventoryBox_C.ExecuteUbergraph_PlayerDeadInventoryBox
// (HasDefaults)
// Parameters:
// int EntryPoint (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void APlayerDeadInventoryBox_C::ExecuteUbergraph_PlayerDeadInventoryBox(int EntryPoint)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerDeadInventoryBox.PlayerDeadInventoryBox_C.ExecuteUbergraph_PlayerDeadInventoryBox");

	APlayerDeadInventoryBox_C_ExecuteUbergraph_PlayerDeadInventoryBox_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


}

