#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Parameters
//---------------------By BangJO---------------------------

// Function AnimNotify_AkEvent.AnimNotify_AkEvent_C.TryGetOwnerPawn
struct UAnimNotify_AkEvent_C_TryGetOwnerPawn_Params
{
	class AActor* Owner; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class APawn* Pawn; // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function AnimNotify_AkEvent.AnimNotify_AkEvent_C.GetEvent
struct UAnimNotify_AkEvent_C_GetEvent_Params
{
	class USkeletalMeshComponent* MeshComp; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UAkAudioEvent* OutEvent; // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function AnimNotify_AkEvent.AnimNotify_AkEvent_C.Received_Notify
struct UAnimNotify_AkEvent_C_Received_Notify_Params
{
	class USkeletalMeshComponent** MeshComp; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UAnimSequenceBase** Animation; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool ReturnValue; // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

}

