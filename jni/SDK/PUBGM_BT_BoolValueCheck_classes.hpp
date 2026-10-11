#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass BT_BoolValueCheck.BT_BoolValueCheck_C
// 0x0031 (0x00C9 - 0x0098)
class UBT_BoolValueCheck_C : public UBTDecorator_BlueprintBase
{
public:
	struct FPointerToUberGraphFrame UberGraphFrame; // 0x0098(0x0008) (Transient, DuplicateTransient)
	struct FBlackboardKeySelector BoolKey; // 0x00A0(0x0028) (Edit, BlueprintVisible)
	bool TargetValue; // 0x00C8(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass BT_BoolValueCheck.BT_BoolValueCheck_C");
		return pStaticClass;
	}


	bool PerformConditionCheck(class AActor** OwnerActor);
	void ExecuteUbergraph_BT_BoolValueCheck(int EntryPoint);
};


}

