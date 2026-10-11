// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Functions
//---------------------By BangJO---------------------------

// Function Title_UIBP.Title_UIBP_C.SetAliasInfo
// (Public, BlueprintCallable, BlueprintEvent)
// Parameters:
// int ID (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FString Title (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
// struct FString Nation (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
// float Available_len (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// int RankID (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UTitle_UIBP_C::SetAliasInfo(int ID, const struct FString& Title, const struct FString& Nation, float Available_len, int RankID)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Title_UIBP.Title_UIBP_C.SetAliasInfo");

	UTitle_UIBP_C_SetAliasInfo_Params params;
	params.ID = ID;
	params.Title = Title;
	params.Nation = Nation;
	params.Available_len = Available_len;
	params.RankID = RankID;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Title_UIBP.Title_UIBP_C.PreConstruct
// (BlueprintCosmetic, Event, Public, BlueprintEvent)
// Parameters:
// bool* IsDesignTime (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UTitle_UIBP_C::PreConstruct(bool* IsDesignTime)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Title_UIBP.Title_UIBP_C.PreConstruct");

	UTitle_UIBP_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Title_UIBP.Title_UIBP_C.ExecuteUbergraph_Title_UIBP
// (HasDefaults)
// Parameters:
// int EntryPoint (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UTitle_UIBP_C::ExecuteUbergraph_Title_UIBP(int EntryPoint)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Title_UIBP.Title_UIBP_C.ExecuteUbergraph_Title_UIBP");

	UTitle_UIBP_C_ExecuteUbergraph_Title_UIBP_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


}

