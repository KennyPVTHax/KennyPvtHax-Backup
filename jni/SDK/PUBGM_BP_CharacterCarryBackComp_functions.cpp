// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Functions
//---------------------By BangJO---------------------------

// Function BP_CharacterCarryBackComp.BP_CharacterCarryBackComp_C.FindFreedomLocationAndRotation
// (Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
// Parameters:
// class ACharacter* Character (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool bValid (Parm, OutParm, ZeroConstructor, IsPlainOldData)
// struct FVector Location (Parm, OutParm, IsPlainOldData)
// struct FRotator Rotation (Parm, OutParm, IsPlainOldData)

void UBP_CharacterCarryBackComp_C::FindFreedomLocationAndRotation(class ACharacter* Character, bool* bValid, struct FVector* Location, struct FRotator* Rotation)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function BP_CharacterCarryBackComp.BP_CharacterCarryBackComp_C.FindFreedomLocationAndRotation");

	UBP_CharacterCarryBackComp_C_FindFreedomLocationAndRotation_Params params;
	params.Character = Character;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	if (bValid != nullptr)
		*bValid = params.bValid;
	if (Location != nullptr)
		*Location = params.Location;
	if (Rotation != nullptr)
		*Rotation = params.Rotation;
}


}

