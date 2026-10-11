#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass ChangePetState.ChangePetState_C
// 0x000A (0x00AA - 0x00A0)
class UChangePetState_C : public UBTTask_BlueprintBase
{
public:
	struct FPointerToUberGraphFrame UberGraphFrame; // 0x00A0(0x0008) (Transient, DuplicateTransient)
	TEnumAsByte<enum EPetState> State; // 0x00A8(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<enum EPawnStateChangeType> ChangeType; // 0x00A9(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass ChangePetState.ChangePetState_C");
		return pStaticClass;
	}


	void ReceiveExecuteAI(class AAIController** OwnerController, class APawn** ControlledPawn);
	void ExecuteUbergraph_ChangePetState(int EntryPoint);
};


}

