// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Functions
//---------------------By BangJO---------------------------

// Function SmartAssistant_RobotTips_UIBP.SmartAssistant_RobotTips_UIBP_C.Tick
// (BlueprintCosmetic, Event, Public, BlueprintEvent)
// Parameters:
// struct FGeometry* MyGeometry (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float* InDeltaTime (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void USmartAssistant_RobotTips_UIBP_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function SmartAssistant_RobotTips_UIBP.SmartAssistant_RobotTips_UIBP_C.Tick");

	USmartAssistant_RobotTips_UIBP_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function SmartAssistant_RobotTips_UIBP.SmartAssistant_RobotTips_UIBP_C.ExecuteUbergraph_SmartAssistant_RobotTips_UIBP
// (HasDefaults)
// Parameters:
// int EntryPoint (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void USmartAssistant_RobotTips_UIBP_C::ExecuteUbergraph_SmartAssistant_RobotTips_UIBP(int EntryPoint)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function SmartAssistant_RobotTips_UIBP.SmartAssistant_RobotTips_UIBP_C.ExecuteUbergraph_SmartAssistant_RobotTips_UIBP");

	USmartAssistant_RobotTips_UIBP_C_ExecuteUbergraph_SmartAssistant_RobotTips_UIBP_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


}

