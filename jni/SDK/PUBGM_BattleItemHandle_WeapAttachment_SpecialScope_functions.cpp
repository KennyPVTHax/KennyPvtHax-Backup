// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Functions
//---------------------By BangJO---------------------------

// Function BattleItemHandle_WeapAttachment_SpecialScope.BattleItemHandle_WeapAttachment_SpecialScope_C.GetFov
// (Public, HasOutParms, BlueprintCallable, BlueprintEvent)
// Parameters:
// float FOV (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UBattleItemHandle_WeapAttachment_SpecialScope_C::GetFov(float* FOV)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function BattleItemHandle_WeapAttachment_SpecialScope.BattleItemHandle_WeapAttachment_SpecialScope_C.GetFov");

	UBattleItemHandle_WeapAttachment_SpecialScope_C_GetFov_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	if (FOV != nullptr)
		*FOV = params.FOV;
}


}

