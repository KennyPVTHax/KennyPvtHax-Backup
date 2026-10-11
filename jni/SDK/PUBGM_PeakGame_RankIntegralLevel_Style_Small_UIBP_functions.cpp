// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Functions
//---------------------By BangJO---------------------------

// Function PeakGame_RankIntegralLevel_Style_Small_UIBP.PeakGame_RankIntegralLevel_Style_Small_UIBP_C.GetPreviewPath
// (Public, HasOutParms, BlueprintCallable, BlueprintEvent)
// Parameters:
// struct FString BPPath (Parm, OutParm, ZeroConstructor)

void UPeakGame_RankIntegralLevel_Style_Small_UIBP_C::GetPreviewPath(struct FString* BPPath)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PeakGame_RankIntegralLevel_Style_Small_UIBP.PeakGame_RankIntegralLevel_Style_Small_UIBP_C.GetPreviewPath");

	UPeakGame_RankIntegralLevel_Style_Small_UIBP_C_GetPreviewPath_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	if (BPPath != nullptr)
		*BPPath = params.BPPath;
}


// Function PeakGame_RankIntegralLevel_Style_Small_UIBP.PeakGame_RankIntegralLevel_Style_Small_UIBP_C.ConstructPreviewSubItem
// (Public, HasDefaults, BlueprintCallable, BlueprintEvent)

void UPeakGame_RankIntegralLevel_Style_Small_UIBP_C::ConstructPreviewSubItem()
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PeakGame_RankIntegralLevel_Style_Small_UIBP.PeakGame_RankIntegralLevel_Style_Small_UIBP_C.ConstructPreviewSubItem");

	UPeakGame_RankIntegralLevel_Style_Small_UIBP_C_ConstructPreviewSubItem_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PeakGame_RankIntegralLevel_Style_Small_UIBP.PeakGame_RankIntegralLevel_Style_Small_UIBP_C.PreConstruct
// (BlueprintCosmetic, Event, Public, BlueprintEvent)
// Parameters:
// bool* IsDesignTime (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UPeakGame_RankIntegralLevel_Style_Small_UIBP_C::PreConstruct(bool* IsDesignTime)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PeakGame_RankIntegralLevel_Style_Small_UIBP.PeakGame_RankIntegralLevel_Style_Small_UIBP_C.PreConstruct");

	UPeakGame_RankIntegralLevel_Style_Small_UIBP_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PeakGame_RankIntegralLevel_Style_Small_UIBP.PeakGame_RankIntegralLevel_Style_Small_UIBP_C.ExecuteUbergraph_PeakGame_RankIntegralLevel_Style_Small_UIBP
// ()
// Parameters:
// int EntryPoint (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UPeakGame_RankIntegralLevel_Style_Small_UIBP_C::ExecuteUbergraph_PeakGame_RankIntegralLevel_Style_Small_UIBP(int EntryPoint)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PeakGame_RankIntegralLevel_Style_Small_UIBP.PeakGame_RankIntegralLevel_Style_Small_UIBP_C.ExecuteUbergraph_PeakGame_RankIntegralLevel_Style_Small_UIBP");

	UPeakGame_RankIntegralLevel_Style_Small_UIBP_C_ExecuteUbergraph_PeakGame_RankIntegralLevel_Style_Small_UIBP_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


}

