#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass PetSpecifiedAnim.PetSpecifiedAnim_C
// 0x0010 (0x00B0 - 0x00A0)
class UPetSpecifiedAnim_C : public UBTTask_BlueprintBase
{
public:
	struct FPointerToUberGraphFrame UberGraphFrame; // 0x00A0(0x0008) (Transient, DuplicateTransient)
	struct FName AnimationID; // 0x00A8(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass PetSpecifiedAnim.PetSpecifiedAnim_C");
		return pStaticClass;
	}


	void ReceiveExecuteAI(class AAIController** OwnerController, class APawn** ControlledPawn);
	void ExecuteUbergraph_PetSpecifiedAnim(int EntryPoint);
};


}

