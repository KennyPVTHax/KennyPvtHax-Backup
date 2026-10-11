#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Parameters
//---------------------By BangJO---------------------------

// Function CreativeLua.CreativeBridgeLuaVM.UGCLuaError
struct UCreativeBridgeLuaVM_UGCLuaError_Params
{
	int ErrCode; // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function CreativeLua.CreativeBridgeLuaVM.SetUGCSuspendStateFix
struct UCreativeBridgeLuaVM_SetUGCSuspendStateFix_Params
{
	bool bEnable; // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function CreativeLua.CreativeBridgeLuaVM.RegisterSluaCallUgcluaEventHandler
struct UCreativeBridgeLuaVM_RegisterSluaCallUgcluaEventHandler_Params
{
};

// Function CreativeLua.CreativeBridgeLuaVM.PostInit
struct UCreativeBridgeLuaVM_PostInit_Params
{
};

// Function CreativeLua.CreativeBridgeLuaVM.GetUGCSuspendStateFix
struct UCreativeBridgeLuaVM_GetUGCSuspendStateFix_Params
{
	bool ReturnValue; // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function CreativeLua.CreativeEnvLuaVMFactory.CreateCreativeEnvLuaVM
struct UCreativeEnvLuaVMFactory_CreateCreativeEnvLuaVM_Params
{
	struct FString InLuaFilePath; // (Parm, ZeroConstructor)
	class UObject* WorldContextObject; // (Parm, ZeroConstructor, IsPlainOldData)
	class UCreativeEnvLuaVM* ReturnValue; // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

}

