// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Functions
//---------------------By BangJO---------------------------

// Function BP_AvatarColor_Base.BP_AvatarColor_Base_C.SetCustomColorDeffered
// (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent)
// Parameters:
// class UMaterialInterface** InMaterial (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FSlotToMatColor* InMatColor (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void UBP_AvatarColor_Base_C::SetCustomColorDeffered(class UMaterialInterface** InMaterial, struct FSlotToMatColor* InMatColor)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function BP_AvatarColor_Base.BP_AvatarColor_Base_C.SetCustomColorDeffered");

	UBP_AvatarColor_Base_C_SetCustomColorDeffered_Params params;
	params.InMaterial = InMaterial;
	params.InMatColor = InMatColor;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function BP_AvatarColor_Base.BP_AvatarColor_Base_C.ExecuteUbergraph_BP_AvatarColor_Base
// (HasDefaults)
// Parameters:
// int EntryPoint (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_AvatarColor_Base_C::ExecuteUbergraph_BP_AvatarColor_Base(int EntryPoint)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function BP_AvatarColor_Base.BP_AvatarColor_Base_C.ExecuteUbergraph_BP_AvatarColor_Base");

	UBP_AvatarColor_Base_C_ExecuteUbergraph_BP_AvatarColor_Base_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


}

