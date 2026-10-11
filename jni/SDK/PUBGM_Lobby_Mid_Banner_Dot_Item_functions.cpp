// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Functions
//---------------------By BangJO---------------------------

// Function Lobby_Mid_Banner_Dot_Item.Lobby_Mid_Banner_Dot_Item_C.SetData
// (Public, BlueprintCallable, BlueprintEvent)
// Parameters:
// bool bSelect (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ULobby_Mid_Banner_Dot_Item_C::SetData(bool bSelect)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Lobby_Mid_Banner_Dot_Item.Lobby_Mid_Banner_Dot_Item_C.SetData");

	ULobby_Mid_Banner_Dot_Item_C_SetData_Params params;
	params.bSelect = bSelect;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


}

