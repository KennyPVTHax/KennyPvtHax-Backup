#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass BP_VehicleShootDriverComponent.BP_VehicleShootDriverComponent_C
// 0x0008 (0x0400 - 0x03F8)
class UBP_VehicleShootDriverComponent_C : public UVehicleShootDriverComponent
{
public:
	struct FPointerToUberGraphFrame UberGraphFrame; // 0x03F8(0x0008) (Transient, DuplicateTransient)

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass BP_VehicleShootDriverComponent.BP_VehicleShootDriverComponent_C");
		return pStaticClass;
	}


	void ReceiveBeginPlay();
	void ReceiveEndPlay(TEnumAsByte<enum EEndPlayReason>* EndPlayReason);
	void ExecuteUbergraph_BP_VehicleShootDriverComponent(int EntryPoint);
};


}

