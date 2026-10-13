// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Functions
//---------------------By BangJO---------------------------

// Function MaskBoxItem.MaskBoxItem_C.Construct
// (BlueprintCosmetic, Event, Public, BlueprintEvent)

void UMaskBoxItem_C::Construct()
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function MaskBoxItem.MaskBoxItem_C.Construct");

	UMaskBoxItem_C_Construct_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function MaskBoxItem.MaskBoxItem_C.ExecuteUbergraph_MaskBoxItem
// ()
// Parameters:
// int EntryPoint (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UMaskBoxItem_C::ExecuteUbergraph_MaskBoxItem(int EntryPoint)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function MaskBoxItem.MaskBoxItem_C.ExecuteUbergraph_MaskBoxItem");

	UMaskBoxItem_C_ExecuteUbergraph_MaskBoxItem_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


}

