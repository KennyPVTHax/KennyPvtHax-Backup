// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Functions
//---------------------By BangJO---------------------------

// Function iTOP.FBHelper.DelayToSetAutoInitFacebookLog
// (Final, Native, Static, Public, BlueprintCallable)
// Parameters:
// bool IsAutoInit (Parm, ZeroConstructor, IsPlainOldData)

void UFBHelper::DelayToSetAutoInitFacebookLog(bool IsAutoInit)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function iTOP.FBHelper.DelayToSetAutoInitFacebookLog");

	UFBHelper_DelayToSetAutoInitFacebookLog_Params params;
	params.IsAutoInit = IsAutoInit;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	static auto defaultObj = StaticClass()->GetDefaultObject();
	defaultObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function iTOP.FBHelper.DelayToInitFacebookSDK
// (Final, Native, Static, Public, BlueprintCallable)
// Parameters:
// bool IsAutoInit (Parm, ZeroConstructor, IsPlainOldData)
// bool WithLaunchOption (Parm, ZeroConstructor, IsPlainOldData)

void UFBHelper::DelayToInitFacebookSDK(bool IsAutoInit, bool WithLaunchOption)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function iTOP.FBHelper.DelayToInitFacebookSDK");

	UFBHelper_DelayToInitFacebookSDK_Params params;
	params.IsAutoInit = IsAutoInit;
	params.WithLaunchOption = WithLaunchOption;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	static auto defaultObj = StaticClass()->GetDefaultObject();
	defaultObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


}

