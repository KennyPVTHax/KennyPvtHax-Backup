#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass BP_DamageNumberHUD.BP_DamageNumberHUD_C
// 0x0000 (0x0128 - 0x0128)
class UBP_DamageNumberHUD_C : public UDamageNumberWidget
{
public:

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass BP_DamageNumberHUD.BP_DamageNumberHUD_C");
		return pStaticClass;
	}

};


}

