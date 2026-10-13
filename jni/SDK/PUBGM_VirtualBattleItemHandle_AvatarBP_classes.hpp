#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass VirtualBattleItemHandle_AvatarBP.VirtualBattleItemHandle_AvatarBP_C
// 0x000E (0x0BA0 - 0x0B92)
class UVirtualBattleItemHandle_AvatarBP_C : public UBattleItemHandle_AvatarBP_C
{
public:
	unsigned char UnknownData00[0x6]; // 0x0B92(0x0006) MISSED OFFSET
	struct FPointerToUberGraphFrame UberGraphFrame; // 0x0B98(0x0008) (Transient, DuplicateTransient)

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass VirtualBattleItemHandle_AvatarBP.VirtualBattleItemHandle_AvatarBP_C");
		return pStaticClass;
	}


	void GetWrapperClass(class UClass** WrapperClass);
	void Constuct(struct FItemDefineID* InDefineID);
	void ExecuteUbergraph_VirtualBattleItemHandle_AvatarBP(int EntryPoint);
};


}

