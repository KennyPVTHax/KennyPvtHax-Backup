// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Functions
//---------------------By BangJO---------------------------

// Function BP_Phone_Anim.BP_Phone_Anim_C.AnimNotify_ShowPhone
// (BlueprintCallable, BlueprintEvent)

void UBP_Phone_Anim_C::AnimNotify_ShowPhone()
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function BP_Phone_Anim.BP_Phone_Anim_C.AnimNotify_ShowPhone");

	UBP_Phone_Anim_C_AnimNotify_ShowPhone_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function BP_Phone_Anim.BP_Phone_Anim_C.ExecuteUbergraph_BP_Phone_Anim
// ()
// Parameters:
// int EntryPoint (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_Phone_Anim_C::ExecuteUbergraph_BP_Phone_Anim(int EntryPoint)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function BP_Phone_Anim.BP_Phone_Anim_C.ExecuteUbergraph_BP_Phone_Anim");

	UBP_Phone_Anim_C_ExecuteUbergraph_BP_Phone_Anim_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


}

