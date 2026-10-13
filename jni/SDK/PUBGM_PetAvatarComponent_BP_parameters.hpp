#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Parameters
//---------------------By BangJO---------------------------

// Function PetAvatarComponent_BP.PetAvatarComponent_BP_C.GetFakeAvatarHandleItem
struct UPetAvatarComponent_BP_C_GetFakeAvatarHandleItem_Params
{
	int* InSlotID; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int* InItemID; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int* AdditionalItemID; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int ReturnValue; // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function PetAvatarComponent_BP.PetAvatarComponent_BP_C.PetHasEquippedItem
struct UPetAvatarComponent_BP_C_PetHasEquippedItem_Params
{
	int ID; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool Out; // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function PetAvatarComponent_BP.PetAvatarComponent_BP_C.PetUnequipItemById
struct UPetAvatarComponent_BP_C_PetUnequipItemById_Params
{
	int ID; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function PetAvatarComponent_BP.PetAvatarComponent_BP_C.PetEquipItemById
struct UPetAvatarComponent_BP_C_PetEquipItemById_Params
{
	int ID; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

