#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Parameters
//---------------------By BangJO---------------------------

// Function BP_AvatarPattern_Base.BP_AvatarPattern_Base_C.GetPatternNumTexturePath
struct UBP_AvatarPattern_Base_C_GetPatternNumTexturePath_Params
{
	int* InNumID; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FSoftObjectPath OutTexture1; // (Parm, OutParm)
	struct FSoftObjectPath OutTexture2; // (Parm, OutParm)
};

// Function BP_AvatarPattern_Base.BP_AvatarPattern_Base_C.SetCustomPattern_Implementation
struct UBP_AvatarPattern_Base_C_SetCustomPattern_Implementation_Params
{
	class UMaterialInterface* InMaterial; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FSlotToMatPattern InMatPattern; // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function BP_AvatarPattern_Base.BP_AvatarPattern_Base_C.SetCustomPatternNum_Implementation
struct UBP_AvatarPattern_Base_C_SetCustomPatternNum_Implementation_Params
{
	class UMaterialInterface* InMaterial; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FSlotToMatPattern InMatPattern; // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function BP_AvatarPattern_Base.BP_AvatarPattern_Base_C.SetCustomPatternDeffered
struct UBP_AvatarPattern_Base_C_SetCustomPatternDeffered_Params
{
	class UMaterialInterface** InMaterial; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FSlotToMatPattern* InMatPattern; // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function BP_AvatarPattern_Base.BP_AvatarPattern_Base_C.ExecuteUbergraph_BP_AvatarPattern_Base
struct UBP_AvatarPattern_Base_C_ExecuteUbergraph_BP_AvatarPattern_Base_Params
{
	int EntryPoint; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

