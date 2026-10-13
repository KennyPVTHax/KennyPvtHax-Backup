// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Functions
//---------------------By BangJO---------------------------

// Function PetEntityComponent_BP.PetEntityComponent_BP_C.GetAttachInfoFromTable
// (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
// Parameters:
// struct FFixPetAttachInfo* Info (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FPetAttachInfo ReturnValue (Parm, OutParm, ReturnParm)

struct FPetAttachInfo UPetEntityComponent_BP_C::GetAttachInfoFromTable(struct FFixPetAttachInfo* Info)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PetEntityComponent_BP.PetEntityComponent_BP_C.GetAttachInfoFromTable");

	UPetEntityComponent_BP_C_GetAttachInfoFromTable_Params params;
	params.Info = Info;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	return params.ReturnValue;
}


}

