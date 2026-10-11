// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Functions
//---------------------By BangJO---------------------------

// Function BP_LobbyVehicle.BP_LobbyVehicle_C.TrySetHighLight
// (Public, BlueprintCallable, BlueprintEvent)
// Parameters:
// float NewParam (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float NewParam1 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float NewParam2 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_LobbyVehicle_C::TrySetHighLight(float NewParam, float NewParam1, float NewParam2)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function BP_LobbyVehicle.BP_LobbyVehicle_C.TrySetHighLight");

	ABP_LobbyVehicle_C_TrySetHighLight_Params params;
	params.NewParam = NewParam;
	params.NewParam1 = NewParam1;
	params.NewParam2 = NewParam2;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function BP_LobbyVehicle.BP_LobbyVehicle_C.SetHighLight
// (Public, BlueprintCallable, BlueprintEvent)
// Parameters:
// float invincible (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float FreExp (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float Speed (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_LobbyVehicle_C::SetHighLight(float invincible, float FreExp, float Speed)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function BP_LobbyVehicle.BP_LobbyVehicle_C.SetHighLight");

	ABP_LobbyVehicle_C_SetHighLight_Params params;
	params.invincible = invincible;
	params.FreExp = FreExp;
	params.Speed = Speed;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function BP_LobbyVehicle.BP_LobbyVehicle_C.SetDMIParam
// (Public, BlueprintCallable, BlueprintEvent)
// Parameters:
// class UMaterialInstanceDynamic* Target (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FName Name (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float Value (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_LobbyVehicle_C::SetDMIParam(class UMaterialInstanceDynamic* Target, const struct FName& Name, float Value)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function BP_LobbyVehicle.BP_LobbyVehicle_C.SetDMIParam");

	ABP_LobbyVehicle_C_SetDMIParam_Params params;
	params.Target = Target;
	params.Name = Name;
	params.Value = Value;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function BP_LobbyVehicle.BP_LobbyVehicle_C.GetVehicleMasterPath
// (Public, HasOutParms, BlueprintCallable, BlueprintEvent, BlueprintPure)
// Parameters:
// int VehicleSkinID (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FString MeshBasePath (Parm, OutParm, ZeroConstructor)

void ABP_LobbyVehicle_C::GetVehicleMasterPath(int VehicleSkinID, struct FString* MeshBasePath)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function BP_LobbyVehicle.BP_LobbyVehicle_C.GetVehicleMasterPath");

	ABP_LobbyVehicle_C_GetVehicleMasterPath_Params params;
	params.VehicleSkinID = VehicleSkinID;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	if (MeshBasePath != nullptr)
		*MeshBasePath = params.MeshBasePath;
}


// Function BP_LobbyVehicle.BP_LobbyVehicle_C.UserConstructionScript
// (Event, Public, BlueprintCallable, BlueprintEvent)

void ABP_LobbyVehicle_C::UserConstructionScript()
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function BP_LobbyVehicle.BP_LobbyVehicle_C.UserConstructionScript");

	ABP_LobbyVehicle_C_UserConstructionScript_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


}

