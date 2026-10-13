#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Parameters
//---------------------By BangJO---------------------------

// Function RankSmall_Interface.RankSmall_Interface_C.SetRankText
struct URankSmall_Interface_C_SetRankText_Params
{
	struct FSlateColor Color; // (BlueprintVisible, BlueprintReadOnly, Parm)
	struct FSlateColor ShadowColor; // (BlueprintVisible, BlueprintReadOnly, Parm)
	struct FSlateFontInfo FontInfo; // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function RankSmall_Interface.RankSmall_Interface_C.SetRankIntegral
struct URankSmall_Interface_C_SetRankIntegral_Params
{
	struct FBP_STRUCT_RankIntegralLevel_type RankIntegralLevel_Info; // (BlueprintVisible, BlueprintReadOnly, Parm)
	bool isStarOpen; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

