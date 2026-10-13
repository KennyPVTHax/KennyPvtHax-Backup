// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Functions
//---------------------By BangJO---------------------------

// Function LobbyPlayEmoteComponent_BP.LobbyPlayEmoteComponent_BP_C.OnEquipmentChange
// (Public, BlueprintCallable, BlueprintEvent)
// Parameters:
// int resID (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool bPutOn (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ULobbyPlayEmoteComponent_BP_C::OnEquipmentChange(int resID, bool bPutOn)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function LobbyPlayEmoteComponent_BP.LobbyPlayEmoteComponent_BP_C.OnEquipmentChange");

	ULobbyPlayEmoteComponent_BP_C_OnEquipmentChange_Params params;
	params.resID = resID;
	params.bPutOn = bPutOn;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function LobbyPlayEmoteComponent_BP.LobbyPlayEmoteComponent_BP_C.OnStartLevelSequence
// (Public, BlueprintCallable, BlueprintEvent)

void ULobbyPlayEmoteComponent_BP_C::OnStartLevelSequence()
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function LobbyPlayEmoteComponent_BP.LobbyPlayEmoteComponent_BP_C.OnStartLevelSequence");

	ULobbyPlayEmoteComponent_BP_C_OnStartLevelSequence_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function LobbyPlayEmoteComponent_BP.LobbyPlayEmoteComponent_BP_C.GetLobbyCamera
// (Public, HasOutParms, BlueprintCallable, BlueprintEvent)
// Parameters:
// class ACameraActor* CameraActor (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void ULobbyPlayEmoteComponent_BP_C::GetLobbyCamera(class ACameraActor** CameraActor)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function LobbyPlayEmoteComponent_BP.LobbyPlayEmoteComponent_BP_C.GetLobbyCamera");

	ULobbyPlayEmoteComponent_BP_C_GetLobbyCamera_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	if (CameraActor != nullptr)
		*CameraActor = params.CameraActor;
}


// Function LobbyPlayEmoteComponent_BP.LobbyPlayEmoteComponent_BP_C.OnStopLevelSequence
// (Public, BlueprintCallable, BlueprintEvent)

void ULobbyPlayEmoteComponent_BP_C::OnStopLevelSequence()
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function LobbyPlayEmoteComponent_BP.LobbyPlayEmoteComponent_BP_C.OnStopLevelSequence");

	ULobbyPlayEmoteComponent_BP_C_OnStopLevelSequence_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function LobbyPlayEmoteComponent_BP.LobbyPlayEmoteComponent_BP_C.ChangetoLevelSequenceCamera
// (Public, BlueprintCallable, BlueprintEvent)

void ULobbyPlayEmoteComponent_BP_C::ChangetoLevelSequenceCamera()
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function LobbyPlayEmoteComponent_BP.LobbyPlayEmoteComponent_BP_C.ChangetoLevelSequenceCamera");

	ULobbyPlayEmoteComponent_BP_C_ChangetoLevelSequenceCamera_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function LobbyPlayEmoteComponent_BP.LobbyPlayEmoteComponent_BP_C.OnTrackEvent
// (Public, BlueprintCallable, BlueprintEvent)
// Parameters:
// struct FString EventData (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)

void ULobbyPlayEmoteComponent_BP_C::OnTrackEvent(const struct FString& EventData)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function LobbyPlayEmoteComponent_BP.LobbyPlayEmoteComponent_BP_C.OnTrackEvent");

	ULobbyPlayEmoteComponent_BP_C_OnTrackEvent_Params params;
	params.EventData = EventData;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function LobbyPlayEmoteComponent_BP.LobbyPlayEmoteComponent_BP_C.PlayCameraEmoteAnim
// (Event, Public, BlueprintEvent)
// Parameters:
// class ULevelSequence** CurrentCameraEmoteAnim (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ULobbyPlayEmoteComponent_BP_C::PlayCameraEmoteAnim(class ULevelSequence** CurrentCameraEmoteAnim)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function LobbyPlayEmoteComponent_BP.LobbyPlayEmoteComponent_BP_C.PlayCameraEmoteAnim");

	ULobbyPlayEmoteComponent_BP_C_PlayCameraEmoteAnim_Params params;
	params.CurrentCameraEmoteAnim = CurrentCameraEmoteAnim;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function LobbyPlayEmoteComponent_BP.LobbyPlayEmoteComponent_BP_C.StopCameraEmoteAnim
// (Event, Public, BlueprintCallable, BlueprintEvent)

void ULobbyPlayEmoteComponent_BP_C::StopCameraEmoteAnim()
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function LobbyPlayEmoteComponent_BP.LobbyPlayEmoteComponent_BP_C.StopCameraEmoteAnim");

	ULobbyPlayEmoteComponent_BP_C_StopCameraEmoteAnim_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function LobbyPlayEmoteComponent_BP.LobbyPlayEmoteComponent_BP_C.ShowAvatarForEmote
// (Event, Public, BlueprintCallable, BlueprintEvent)
// Parameters:
// bool* Show (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool* Force (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ULobbyPlayEmoteComponent_BP_C::ShowAvatarForEmote(bool* Show, bool* Force)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function LobbyPlayEmoteComponent_BP.LobbyPlayEmoteComponent_BP_C.ShowAvatarForEmote");

	ULobbyPlayEmoteComponent_BP_C_ShowAvatarForEmote_Params params;
	params.Show = Show;
	params.Force = Force;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function LobbyPlayEmoteComponent_BP.LobbyPlayEmoteComponent_BP_C.BindEventToCameraSequence
// (Event, Public, BlueprintCallable, BlueprintEvent)
// Parameters:
// class ULevelSequencePlayer** SeqPlayer (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ULobbyPlayEmoteComponent_BP_C::BindEventToCameraSequence(class ULevelSequencePlayer** SeqPlayer)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function LobbyPlayEmoteComponent_BP.LobbyPlayEmoteComponent_BP_C.BindEventToCameraSequence");

	ULobbyPlayEmoteComponent_BP_C_BindEventToCameraSequence_Params params;
	params.SeqPlayer = SeqPlayer;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function LobbyPlayEmoteComponent_BP.LobbyPlayEmoteComponent_BP_C.ExecuteUbergraph_LobbyPlayEmoteComponent_BP
// ()
// Parameters:
// int EntryPoint (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ULobbyPlayEmoteComponent_BP_C::ExecuteUbergraph_LobbyPlayEmoteComponent_BP(int EntryPoint)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function LobbyPlayEmoteComponent_BP.LobbyPlayEmoteComponent_BP_C.ExecuteUbergraph_LobbyPlayEmoteComponent_BP");

	ULobbyPlayEmoteComponent_BP_C_ExecuteUbergraph_LobbyPlayEmoteComponent_BP_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


}

