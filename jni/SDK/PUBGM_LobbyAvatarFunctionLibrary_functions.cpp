// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Functions
//---------------------By BangJO---------------------------

// Function LobbyAvatarFunctionLibrary.LobbyAvatarFunctionLibrary_C.OnPlayerRotate
// (Static, Public, BlueprintCallable, BlueprintEvent)
// Parameters:
// class UCharacterAvatarComp2_BP_C* AvatarComp (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UObject* __WorldContext (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ULobbyAvatarFunctionLibrary_C::OnPlayerRotate(class UCharacterAvatarComp2_BP_C* AvatarComp, class UObject* __WorldContext)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function LobbyAvatarFunctionLibrary.LobbyAvatarFunctionLibrary_C.OnPlayerRotate");

	ULobbyAvatarFunctionLibrary_C_OnPlayerRotate_Params params;
	params.AvatarComp = AvatarComp;
	params.__WorldContext = __WorldContext;

	auto flags = pFunc->FunctionFlags;

	static auto defaultObj = StaticClass()->GetDefaultObject();
	defaultObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


}

