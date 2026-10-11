#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass PetEntityComponent_BP.PetEntityComponent_BP_C
// 0x0000 (0x0238 - 0x0238)
class UPetEntityComponent_BP_C : public UPetEntityComponent
{
public:

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass PetEntityComponent_BP.PetEntityComponent_BP_C");
		return pStaticClass;
	}


	struct FPetAttachInfo GetAttachInfoFromTable(struct FFixPetAttachInfo* Info);
};


}

