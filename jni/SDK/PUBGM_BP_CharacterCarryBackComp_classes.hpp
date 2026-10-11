#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass BP_CharacterCarryBackComp.BP_CharacterCarryBackComp_C
// 0x0010 (0x0398 - 0x0388)
class UBP_CharacterCarryBackComp_C : public USTCharacterCarryBackComp
{
public:
	TArray<struct FVector> PutDownLocationOffset; // 0x0388(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass BP_CharacterCarryBackComp.BP_CharacterCarryBackComp_C");
		return pStaticClass;
	}


	void FindFreedomLocationAndRotation(class ACharacter* Character, bool* bValid, struct FVector* Location, struct FRotator* Rotation);
};


}

