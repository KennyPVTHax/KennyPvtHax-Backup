#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Parameters
//---------------------By BangJO---------------------------

// Function Title_UIBP.Title_UIBP_C.SetAliasInfo
struct UTitle_UIBP_C_SetAliasInfo_Params
{
	int ID; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FString Title; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
	struct FString Nation; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
	float Available_len; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int RankID; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Title_UIBP.Title_UIBP_C.PreConstruct
struct UTitle_UIBP_C_PreConstruct_Params
{
	bool* IsDesignTime; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Title_UIBP.Title_UIBP_C.ExecuteUbergraph_Title_UIBP
struct UTitle_UIBP_C_ExecuteUbergraph_Title_UIBP_Params
{
	int EntryPoint; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

