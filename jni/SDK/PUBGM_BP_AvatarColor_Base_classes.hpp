#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass BP_AvatarColor_Base.BP_AvatarColor_Base_C
// 0x0018 (0x0058 - 0x0040)
class UBP_AvatarColor_Base_C : public UBackpackAvatarItemColor
{
public:
	struct FPointerToUberGraphFrame UberGraphFrame; // 0x0040(0x0008) (Transient, DuplicateTransient)
	TArray<struct FName> MaskColorNames; // 0x0048(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass BP_AvatarColor_Base.BP_AvatarColor_Base_C");
		return pStaticClass;
	}


	void SetCustomColorDeffered(class UMaterialInterface** InMaterial, struct FSlotToMatColor* InMatColor);
	void ExecuteUbergraph_BP_AvatarColor_Base(int EntryPoint);
};


}

