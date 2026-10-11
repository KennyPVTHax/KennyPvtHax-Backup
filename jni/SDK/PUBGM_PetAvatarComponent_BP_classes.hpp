#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass PetAvatarComponent_BP.PetAvatarComponent_BP_C
// 0x0000 (0x0C68 - 0x0C68)
class UPetAvatarComponent_BP_C : public UPetAvatarComponent
{
public:

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass PetAvatarComponent_BP.PetAvatarComponent_BP_C");
		return pStaticClass;
	}


	int GetFakeAvatarHandleItem(int* InSlotID, int* InItemID, int* AdditionalItemID);
	void PetHasEquippedItem(int ID, bool* Out);
	void PetUnequipItemById(int ID);
	void PetEquipItemById(int ID);
};


}

