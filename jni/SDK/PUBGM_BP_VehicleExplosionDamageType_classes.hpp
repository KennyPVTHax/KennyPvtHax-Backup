#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass BP_VehicleExplosionDamageType.BP_VehicleExplosionDamageType_C
// 0x0000 (0x0158 - 0x0158)
class UBP_VehicleExplosionDamageType_C : public USTExtraDamageType
{
public:

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass BP_VehicleExplosionDamageType.BP_VehicleExplosionDamageType_C");
		return pStaticClass;
	}

};


}

