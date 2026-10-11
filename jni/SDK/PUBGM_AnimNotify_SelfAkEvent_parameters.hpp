#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Parameters
//---------------------By BangJO---------------------------

// Function AnimNotify_SelfAkEvent.AnimNotify_SelfAkEvent_C.PlayAkEvent
struct UAnimNotify_SelfAkEvent_C_PlayAkEvent_Params
{
	class USkeletalMeshComponent* MeshComp; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool ReturnValue; // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AnimNotify_SelfAkEvent.AnimNotify_SelfAkEvent_C.Received_Notify
struct UAnimNotify_SelfAkEvent_C_Received_Notify_Params
{
	class USkeletalMeshComponent** MeshComp; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UAnimSequenceBase** Animation; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool ReturnValue; // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

}

