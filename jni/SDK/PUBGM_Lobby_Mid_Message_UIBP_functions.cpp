// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Functions
//---------------------By BangJO---------------------------

// Function Lobby_Mid_Message_UIBP.Lobby_Mid_Message_UIBP_C.PreConstruct
// (BlueprintCosmetic, Event, Public, BlueprintEvent)
// Parameters:
// bool* IsDesignTime (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ULobby_Mid_Message_UIBP_C::PreConstruct(bool* IsDesignTime)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Lobby_Mid_Message_UIBP.Lobby_Mid_Message_UIBP_C.PreConstruct");

	ULobby_Mid_Message_UIBP_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Lobby_Mid_Message_UIBP.Lobby_Mid_Message_UIBP_C.ExecuteUbergraph_Lobby_Mid_Message_UIBP
// ()
// Parameters:
// int EntryPoint (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ULobby_Mid_Message_UIBP_C::ExecuteUbergraph_Lobby_Mid_Message_UIBP(int EntryPoint)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Lobby_Mid_Message_UIBP.Lobby_Mid_Message_UIBP_C.ExecuteUbergraph_Lobby_Mid_Message_UIBP");

	ULobby_Mid_Message_UIBP_C_ExecuteUbergraph_Lobby_Mid_Message_UIBP_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


}

