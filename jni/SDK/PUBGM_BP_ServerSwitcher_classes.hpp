#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass BP_ServerSwitcher.BP_ServerSwitcher_C
// 0x0008 (0x01E8 - 0x01E0)
class UBP_ServerSwitcher_C : public UServerSwitchComponent
{
public:
	struct FPointerToUberGraphFrame UberGraphFrame; // 0x01E0(0x0008) (Transient, DuplicateTransient)

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass BP_ServerSwitcher.BP_ServerSwitcher_C");
		return pStaticClass;
	}


	void ReceiveBeginPlay();
	void CustomEvent_1(bool BoolValue);
	void ExecuteUbergraph_BP_ServerSwitcher(int EntryPoint);
};


}

