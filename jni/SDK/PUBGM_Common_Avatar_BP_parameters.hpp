#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Parameters
//---------------------By BangJO---------------------------

// Function Common_Avatar_BP.Common_Avatar_BP_C.SetAssetLoadingMethod
struct UCommon_Avatar_BP_C_SetAssetLoadingMethod_Params
{
	bool Async; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Common_Avatar_BP.Common_Avatar_BP_C.InitView
struct UCommon_Avatar_BP_C_InitView_Params
{
	int Style; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FString UID; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
	struct FString iconUrl; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
	int Gender; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int frameLevel; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int PlayerLevel; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool ignoreFrame; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FString RoleNation; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
};

// Function Common_Avatar_BP.Common_Avatar_BP_C.DownloadSuc__DelegateSignature
struct UCommon_Avatar_BP_C_DownloadSuc__DelegateSignature_Params
{
};

// Function Common_Avatar_BP.Common_Avatar_BP_C.OnClickItemCallback__DelegateSignature
struct UCommon_Avatar_BP_C_OnClickItemCallback__DelegateSignature_Params
{
	struct FString UID; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
};

}

