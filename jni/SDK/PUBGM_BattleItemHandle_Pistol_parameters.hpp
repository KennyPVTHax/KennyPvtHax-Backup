#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Parameters
//---------------------By BangJO---------------------------

// Function BattleItemHandle_Pistol.BattleItemHandle_Pistol_C.GetWrapperClass
struct UBattleItemHandle_Pistol_C_GetWrapperClass_Params
{
	bool found; // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	class UClass* WrapperClass; // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BattleItemHandle_Pistol.BattleItemHandle_Pistol_C.HandleWeaponDestroy
struct UBattleItemHandle_Pistol_C_HandleWeaponDestroy_Params
{
	EBattleItemDisuseReason Reason; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BattleItemHandle_Pistol.BattleItemHandle_Pistol_C.IsMainSlotsHaveWeapon
struct UBattleItemHandle_Pistol_C_IsMainSlotsHaveWeapon_Params
{
	bool HasWeapon; // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BattleItemHandle_Pistol.BattleItemHandle_Pistol_C.GetOwingtWeapon
struct UBattleItemHandle_Pistol_C_GetOwingtWeapon_Params
{
	class ASTExtraWeapon* NewParam; // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BattleItemHandle_Pistol.BattleItemHandle_Pistol_C.LocalHandleDisuse
struct UBattleItemHandle_Pistol_C_LocalHandleDisuse_Params
{
	EBattleItemDisuseReason Reason; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BattleItemHandle_Pistol.BattleItemHandle_Pistol_C.GetAvailableTargetLogicSocketName
struct UBattleItemHandle_Pistol_C_GetAvailableTargetLogicSocketName_Params
{
	struct FName TargetSocket; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FName Ret; // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	bool bNeedPutDownOldWeapon; // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	bool bAutoUse; // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BattleItemHandle_Pistol.BattleItemHandle_Pistol_C.GetAvailableInstantLogicSocketName
struct UBattleItemHandle_Pistol_C_GetAvailableInstantLogicSocketName_Params
{
	struct FName Ret; // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	bool bNeedPutDownOldWeapon; // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	bool bAutoUse; // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BattleItemHandle_Pistol.BattleItemHandle_Pistol_C.CreateWrapperOnGround
struct UBattleItemHandle_Pistol_C_CreateWrapperOnGround_Params
{
};

// Function BattleItemHandle_Pistol.BattleItemHandle_Pistol_C.HandlePickup
struct UBattleItemHandle_Pistol_C_HandlePickup_Params
{
	TScriptInterface<class UItemContainerInterface> ItemContainer; // (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	struct FBattleItemPickupInfo* PickupInfo; // (BlueprintVisible, BlueprintReadOnly, Parm)
	EBattleItemPickupReason* Reason; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool ReturnValue; // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BattleItemHandle_Pistol.BattleItemHandle_Pistol_C.HandleUse
struct UBattleItemHandle_Pistol_C_HandleUse_Params
{
	struct FBattleItemUseTarget* Target; // (BlueprintVisible, BlueprintReadOnly, Parm)
	EBattleItemUseReason* Reason; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool ReturnValue; // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BattleItemHandle_Pistol.BattleItemHandle_Pistol_C.HandleDrop
struct UBattleItemHandle_Pistol_C_HandleDrop_Params
{
	int* InCount; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	EBattleItemDropReason* Reason; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool ReturnValue; // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BattleItemHandle_Pistol.BattleItemHandle_Pistol_C.HandleDisuse
struct UBattleItemHandle_Pistol_C_HandleDisuse_Params
{
	EBattleItemDisuseReason* Reason; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool ReturnValue; // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

}

