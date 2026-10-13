// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Functions
//---------------------By BangJO---------------------------

// Function Newbie_Banner.Newbie_Banner_C.GetOffset
// (Public, HasOutParms, BlueprintCallable, BlueprintEvent)
// Parameters:
// float Offset (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UNewbie_Banner_C::GetOffset(float* Offset)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Newbie_Banner.Newbie_Banner_C.GetOffset");

	UNewbie_Banner_C_GetOffset_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	if (Offset != nullptr)
		*Offset = params.Offset;
}


// Function Newbie_Banner.Newbie_Banner_C.GetCurrentIndex
// (Public, HasOutParms, BlueprintCallable, BlueprintEvent)
// Parameters:
// int Index (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UNewbie_Banner_C::GetCurrentIndex(int* Index)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Newbie_Banner.Newbie_Banner_C.GetCurrentIndex");

	UNewbie_Banner_C_GetCurrentIndex_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	if (Index != nullptr)
		*Index = params.Index;
}


// Function Newbie_Banner.Newbie_Banner_C.OnClickActivityItem
// (Public, BlueprintCallable, BlueprintEvent)
// Parameters:
// class ULobby_Activity_BtnItem_C* Item (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UNewbie_Banner_C::OnClickActivityItem(class ULobby_Activity_BtnItem_C* Item)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Newbie_Banner.Newbie_Banner_C.OnClickActivityItem");

	UNewbie_Banner_C_OnClickActivityItem_Params params;
	params.Item = Item;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Newbie_Banner.Newbie_Banner_C.UpdateCurrentPage
// (Public, HasDefaults, BlueprintCallable, BlueprintEvent)

void UNewbie_Banner_C::UpdateCurrentPage()
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Newbie_Banner.Newbie_Banner_C.UpdateCurrentPage");

	UNewbie_Banner_C_UpdateCurrentPage_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Newbie_Banner.Newbie_Banner_C.SetActivityListPageCount
// (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
// Parameters:
// int pageCount (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UNewbie_Banner_C::SetActivityListPageCount(int pageCount)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Newbie_Banner.Newbie_Banner_C.SetActivityListPageCount");

	UNewbie_Banner_C_SetActivityListPageCount_Params params;
	params.pageCount = pageCount;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Newbie_Banner.Newbie_Banner_C.Tick
// (BlueprintCosmetic, Event, Public, BlueprintEvent)
// Parameters:
// struct FGeometry* MyGeometry (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float* InDeltaTime (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UNewbie_Banner_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Newbie_Banner.Newbie_Banner_C.Tick");

	UNewbie_Banner_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Newbie_Banner.Newbie_Banner_C.ExecuteUbergraph_Newbie_Banner
// (HasDefaults)
// Parameters:
// int EntryPoint (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UNewbie_Banner_C::ExecuteUbergraph_Newbie_Banner(int EntryPoint)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Newbie_Banner.Newbie_Banner_C.ExecuteUbergraph_Newbie_Banner");

	UNewbie_Banner_C_ExecuteUbergraph_Newbie_Banner_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Newbie_Banner.Newbie_Banner_C.EventDispatcherClickItem__DelegateSignature
// (Public, Delegate, BlueprintCallable, BlueprintEvent)
// Parameters:
// int ID (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FString JumpUrl (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)

void UNewbie_Banner_C::EventDispatcherClickItem__DelegateSignature(int ID, const struct FString& JumpUrl)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Newbie_Banner.Newbie_Banner_C.EventDispatcherClickItem__DelegateSignature");

	UNewbie_Banner_C_EventDispatcherClickItem__DelegateSignature_Params params;
	params.ID = ID;
	params.JumpUrl = JumpUrl;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


}

