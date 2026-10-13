// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Functions
//---------------------By BangJO---------------------------

// Function PetUtils.PetUtils_C.GetPetLevelCfg
// (Static, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent, BlueprintPure)
// Parameters:
// struct FGameModePlayerPetInfo PetInfo (BlueprintVisible, BlueprintReadOnly, Parm)
// class UObject* __WorldContext (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FBP_STRUCT_PetLevelTable_type Out_Row (Parm, OutParm)

void UPetUtils_C::GetPetLevelCfg(const struct FGameModePlayerPetInfo& PetInfo, class UObject* __WorldContext, struct FBP_STRUCT_PetLevelTable_type* Out_Row)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PetUtils.PetUtils_C.GetPetLevelCfg");

	UPetUtils_C_GetPetLevelCfg_Params params;
	params.PetInfo = PetInfo;
	params.__WorldContext = __WorldContext;

	auto flags = pFunc->FunctionFlags;

	static auto defaultObj = StaticClass()->GetDefaultObject();
	defaultObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	if (Out_Row != nullptr)
		*Out_Row = params.Out_Row;
}


}

