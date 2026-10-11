// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Functions
//---------------------By BangJO---------------------------

// Function ShineInterface.ShineInterface_C.ShowNormal
// (Public, BlueprintCallable, BlueprintEvent)

void UShineInterface_C::ShowNormal()
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function ShineInterface.ShineInterface_C.ShowNormal");

	UShineInterface_C_ShowNormal_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function ShineInterface.ShineInterface_C.ShowShine
// (Public, BlueprintCallable, BlueprintEvent)

void UShineInterface_C::ShowShine()
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function ShineInterface.ShineInterface_C.ShowShine");

	UShineInterface_C_ShowShine_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


}

