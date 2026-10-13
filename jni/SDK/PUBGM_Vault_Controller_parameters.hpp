#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Parameters
//---------------------By BangJO---------------------------

// Function Vault_Controller.Vault_Controller_C.JumpVault
struct UVault_Controller_C_JumpVault_Params
{
};

// Function Vault_Controller.Vault_Controller_C.VaultServer
struct UVault_Controller_C_VaultServer_Params
{
	float dis; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float Height; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float Length; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FString VaultKey; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
	struct FVector StartPos; // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	class AActor* checkActor; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float crossblockMaxFall; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float crossblockMaxDis; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FVector HitPoint; // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	class AActor* WindowActor; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FRotator MoveDir; // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
};

// Function Vault_Controller.Vault_Controller_C.vaultAll
struct UVault_Controller_C_vaultAll_Params
{
	float dis; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float Height; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float Length; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FString VaultKey; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
	struct FVector StartPos; // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	class AActor* checkActor; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float crossmaxFalling; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float crossmaxDis; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FVector HitPoint; // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FRotator MoveDir; // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
};

// Function Vault_Controller.Vault_Controller_C.StopVault
struct UVault_Controller_C_StopVault_Params
{
};

// Function Vault_Controller.Vault_Controller_C.DsCheckStopVault
struct UVault_Controller_C_DsCheckStopVault_Params
{
};

// Function Vault_Controller.Vault_Controller_C.ExecuteUbergraph_Vault_Controller
struct UVault_Controller_C_ExecuteUbergraph_Vault_Controller_Params
{
	int EntryPoint; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

