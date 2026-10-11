#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Parameters
//---------------------By BangJO---------------------------

// Function BP_CharacterCarryBackComp.BP_CharacterCarryBackComp_C.FindFreedomLocationAndRotation
struct UBP_CharacterCarryBackComp_C_FindFreedomLocationAndRotation_Params
{
	class ACharacter* Character; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool bValid; // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	struct FVector Location; // (Parm, OutParm, IsPlainOldData)
	struct FRotator Rotation; // (Parm, OutParm, IsPlainOldData)
};

}

