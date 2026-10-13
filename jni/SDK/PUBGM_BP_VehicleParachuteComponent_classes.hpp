#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass BP_VehicleParachuteComponent.BP_VehicleParachuteComponent_C
// 0x0010 (0x0268 - 0x0258)
class UBP_VehicleParachuteComponent_C : public UVehicleParachuteComponent
{
public:
	float CameraTargetArmLength; // 0x0258(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FVector CameraRelativeLocation; // 0x025C(0x000C) (Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass BP_VehicleParachuteComponent.BP_VehicleParachuteComponent_C");
		return pStaticClass;
	}

};


}

