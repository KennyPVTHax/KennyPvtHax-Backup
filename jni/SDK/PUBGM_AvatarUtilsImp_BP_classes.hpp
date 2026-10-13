#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass AvatarUtilsImp_BP.AvatarUtilsImp_BP_C
// 0x0000 (0x06B8 - 0x06B8)
class UAvatarUtilsImp_BP_C : public UAvatarBPUtils
{
public:

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass AvatarUtilsImp_BP.AvatarUtilsImp_BP_C");
		return pStaticClass;
	}


	int GetAdjustWeaponBPID_Lobby(int* WeaponId);
	bool GetVehicleDefaultStyleID(int* InVehicleSkinID, TArray<int>* OutStyleIDList);
	struct FString GetVehicleBPPathBySkinID(int* InVehicleSkinID);
	int GetVehicleShapeBySkinID(int* InVehicleSkinID);
	void GetBPTableName(int Type, int TypeSpecificID, struct FString* BPTableName, int* SpecificID);
	class UItemHandleBase* CreateAvatarHandle(struct FItemDefineID* DefineID, class UObject** Outer, bool* bLobby);
	struct FString GetAvatarHandlePath(struct FItemDefineID* DefineID, bool* bLobby);
};


}

