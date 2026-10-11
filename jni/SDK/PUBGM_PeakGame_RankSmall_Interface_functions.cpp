// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Functions
//---------------------By BangJO---------------------------

// Function PeakGame_RankSmall_Interface.PeakGame_RankSmall_Interface_C.SetRankText
// (Public, BlueprintCallable, BlueprintEvent)
// Parameters:
// struct FSlateColor Color (BlueprintVisible, BlueprintReadOnly, Parm)
// struct FSlateColor ShadowColor (BlueprintVisible, BlueprintReadOnly, Parm)
// struct FSlateFontInfo FontInfo (BlueprintVisible, BlueprintReadOnly, Parm)

void UPeakGame_RankSmall_Interface_C::SetRankText(const struct FSlateColor& Color, const struct FSlateColor& ShadowColor, const struct FSlateFontInfo& FontInfo)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PeakGame_RankSmall_Interface.PeakGame_RankSmall_Interface_C.SetRankText");

	UPeakGame_RankSmall_Interface_C_SetRankText_Params params;
	params.Color = Color;
	params.ShadowColor = ShadowColor;
	params.FontInfo = FontInfo;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


}

