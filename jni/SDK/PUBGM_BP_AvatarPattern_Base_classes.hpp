#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass BP_AvatarPattern_Base.BP_AvatarPattern_Base_C
// 0x0008 (0x0080 - 0x0078)
class UBP_AvatarPattern_Base_C : public UBackpackAvatarItemPattern
{
public:
	struct FPointerToUberGraphFrame UberGraphFrame; // 0x0078(0x0008) (Transient, DuplicateTransient)

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass BP_AvatarPattern_Base.BP_AvatarPattern_Base_C");
		return pStaticClass;
	}


	void GetPatternNumTexturePath(int* InNumID, struct FSoftObjectPath* OutTexture1, struct FSoftObjectPath* OutTexture2);
	void SetCustomPattern_Implementation(class UMaterialInterface* InMaterial, const struct FSlotToMatPattern& InMatPattern);
	void SetCustomPatternNum_Implementation(class UMaterialInterface* InMaterial, const struct FSlotToMatPattern& InMatPattern);
	void SetCustomPatternDeffered(class UMaterialInterface** InMaterial, struct FSlotToMatPattern* InMatPattern);
	void ExecuteUbergraph_BP_AvatarPattern_Base(int EntryPoint);
};


}

