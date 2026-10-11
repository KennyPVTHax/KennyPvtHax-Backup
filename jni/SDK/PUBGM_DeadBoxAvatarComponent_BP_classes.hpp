#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass DeadBoxAvatarComponent_BP.DeadBoxAvatarComponent_BP_C
// 0x0000 (0x0568 - 0x0568)
class UDeadBoxAvatarComponent_BP_C : public UDeadBoxAvatarComponent
{
public:

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass DeadBoxAvatarComponent_BP.DeadBoxAvatarComponent_BP_C");
		return pStaticClass;
	}


	void GetVehicleDiedPath(int ItemId, struct FString* Path);
	void IsVehicleAvatarID(int ItemId, bool* IsVehicleAvatarID);
	struct FString GetItemAvatarHandlePath(int* ItemId);
	class UBackpackCommonAvatarHandle* GetItemAvatarHandle(int* ItemId);
};


}

