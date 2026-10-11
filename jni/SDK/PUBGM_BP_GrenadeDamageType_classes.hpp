#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass BP_GrenadeDamageType.BP_GrenadeDamageType_C
// 0x0000 (0x0040 - 0x0040)
class UBP_GrenadeDamageType_C : public UDamageType
{
public:

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass BP_GrenadeDamageType.BP_GrenadeDamageType_C");
		return pStaticClass;
	}

};


}

