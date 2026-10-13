// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Functions
//---------------------By BangJO---------------------------

// Function PetCustomCheckInterface.PetCustomCheckInterface_C.NotAllowAppear
// (Public, HasOutParms, BlueprintCallable, BlueprintEvent)
// Parameters:
// bool Out (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UPetCustomCheckInterface_C::NotAllowAppear(bool* Out)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PetCustomCheckInterface.PetCustomCheckInterface_C.NotAllowAppear");

	UPetCustomCheckInterface_C_NotAllowAppear_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	if (Out != nullptr)
		*Out = params.Out;
}


}

