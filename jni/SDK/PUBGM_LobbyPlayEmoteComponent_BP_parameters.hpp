#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Parameters
//---------------------By BangJO---------------------------

// Function LobbyPlayEmoteComponent_BP.LobbyPlayEmoteComponent_BP_C.OnEquipmentChange
struct ULobbyPlayEmoteComponent_BP_C_OnEquipmentChange_Params
{
	int resID; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool bPutOn; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function LobbyPlayEmoteComponent_BP.LobbyPlayEmoteComponent_BP_C.OnStartLevelSequence
struct ULobbyPlayEmoteComponent_BP_C_OnStartLevelSequence_Params
{
};

// Function LobbyPlayEmoteComponent_BP.LobbyPlayEmoteComponent_BP_C.GetLobbyCamera
struct ULobbyPlayEmoteComponent_BP_C_GetLobbyCamera_Params
{
	class ACameraActor* CameraActor; // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function LobbyPlayEmoteComponent_BP.LobbyPlayEmoteComponent_BP_C.OnStopLevelSequence
struct ULobbyPlayEmoteComponent_BP_C_OnStopLevelSequence_Params
{
};

// Function LobbyPlayEmoteComponent_BP.LobbyPlayEmoteComponent_BP_C.ChangetoLevelSequenceCamera
struct ULobbyPlayEmoteComponent_BP_C_ChangetoLevelSequenceCamera_Params
{
};

// Function LobbyPlayEmoteComponent_BP.LobbyPlayEmoteComponent_BP_C.OnTrackEvent
struct ULobbyPlayEmoteComponent_BP_C_OnTrackEvent_Params
{
	struct FString EventData; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
};

// Function LobbyPlayEmoteComponent_BP.LobbyPlayEmoteComponent_BP_C.PlayCameraEmoteAnim
struct ULobbyPlayEmoteComponent_BP_C_PlayCameraEmoteAnim_Params
{
	class ULevelSequence** CurrentCameraEmoteAnim; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function LobbyPlayEmoteComponent_BP.LobbyPlayEmoteComponent_BP_C.StopCameraEmoteAnim
struct ULobbyPlayEmoteComponent_BP_C_StopCameraEmoteAnim_Params
{
};

// Function LobbyPlayEmoteComponent_BP.LobbyPlayEmoteComponent_BP_C.ShowAvatarForEmote
struct ULobbyPlayEmoteComponent_BP_C_ShowAvatarForEmote_Params
{
	bool* Show; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool* Force; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function LobbyPlayEmoteComponent_BP.LobbyPlayEmoteComponent_BP_C.BindEventToCameraSequence
struct ULobbyPlayEmoteComponent_BP_C_BindEventToCameraSequence_Params
{
	class ULevelSequencePlayer** SeqPlayer; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function LobbyPlayEmoteComponent_BP.LobbyPlayEmoteComponent_BP_C.ExecuteUbergraph_LobbyPlayEmoteComponent_BP
struct ULobbyPlayEmoteComponent_BP_C_ExecuteUbergraph_LobbyPlayEmoteComponent_BP_Params
{
	int EntryPoint; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

