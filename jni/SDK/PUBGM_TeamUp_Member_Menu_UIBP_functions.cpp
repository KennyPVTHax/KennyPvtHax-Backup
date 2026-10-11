// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Functions
//---------------------By BangJO---------------------------

// Function TeamUp_Member_Menu_UIBP.TeamUp_Member_Menu_UIBP_C.Construct
// (BlueprintCosmetic, Event, Public, BlueprintEvent)

void UTeamUp_Member_Menu_UIBP_C::Construct()
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function TeamUp_Member_Menu_UIBP.TeamUp_Member_Menu_UIBP_C.Construct");

	UTeamUp_Member_Menu_UIBP_C_Construct_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function TeamUp_Member_Menu_UIBP.TeamUp_Member_Menu_UIBP_C.ExecuteUbergraph_TeamUp_Member_Menu_UIBP
// ()
// Parameters:
// int EntryPoint (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UTeamUp_Member_Menu_UIBP_C::ExecuteUbergraph_TeamUp_Member_Menu_UIBP(int EntryPoint)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function TeamUp_Member_Menu_UIBP.TeamUp_Member_Menu_UIBP_C.ExecuteUbergraph_TeamUp_Member_Menu_UIBP");

	UTeamUp_Member_Menu_UIBP_C_ExecuteUbergraph_TeamUp_Member_Menu_UIBP_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


}

