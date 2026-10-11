// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Functions
//---------------------By BangJO---------------------------

// Function MinitvAvatarComponent_BP.MinitvAvatarComponent_BP_C.RayEquipItemById
// (Public, BlueprintCallable, BlueprintEvent)
// Parameters:
// int ID (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UMinitvAvatarComponent_BP_C::RayEquipItemById(int ID)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function MinitvAvatarComponent_BP.MinitvAvatarComponent_BP_C.RayEquipItemById");

	UMinitvAvatarComponent_BP_C_RayEquipItemById_Params params;
	params.ID = ID;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


}

