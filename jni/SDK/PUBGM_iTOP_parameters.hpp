#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Parameters
//---------------------By BangJO---------------------------

// Function iTOP.FBHelper.DelayToSetAutoInitFacebookLog
struct UFBHelper_DelayToSetAutoInitFacebookLog_Params
{
	bool IsAutoInit; // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function iTOP.FBHelper.DelayToInitFacebookSDK
struct UFBHelper_DelayToInitFacebookSDK_Params
{
	bool IsAutoInit; // (Parm, ZeroConstructor, IsPlainOldData)
	bool WithLaunchOption; // (Parm, ZeroConstructor, IsPlainOldData)
};

}

