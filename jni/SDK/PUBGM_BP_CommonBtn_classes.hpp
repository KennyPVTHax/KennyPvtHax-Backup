#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass BP_CommonBtn.BP_CommonBtn_C
// 0x000F (0x01A7 - 0x0198)
class UBP_CommonBtn_C : public UCommonBtnComponent
{
public:
	struct FPointerToUberGraphFrame UberGraphFrame; // 0x0198(0x0008) (Transient, DuplicateTransient)
	int OpenMode; // 0x01A0(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TEnumAsByte<enum ECommonBtn> BtnType; // 0x01A4(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool bShow; // 0x01A5(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool bOpen; // 0x01A6(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass BP_CommonBtn.BP_CommonBtn_C");
		return pStaticClass;
	}


	void OnChangeOpenDoorMode(int OpenMode);
	void UnRegistShowDoorButton();
	void OnShowDoorButton(TEnumAsByte<enum ECommonBtn> Type, int OpenParam);
	void RegistShowDoorButton();
	void ShowDoorButton(bool Show, bool Open, int OpenMode);
	void GetPlayerController(class ABP_STExtraPlayerController_C** PlayerController);
	void ReceiveBeginPlay();
	void CharacterStatusChanged(bool IsNearDeath, bool IsRescueingOther);
	void PlayerControllerReconnectedDelegate_Event_1();
	void UI_Click(bool bSimulateExtraDoor, int OpenParam);
	void ToogleDoor();
	void BP_ShowDoorBtn(bool* bShow, bool* bOpen, int* doorOpenMode);
	void AutoOpenDoor(bool BoolValue);
	void BP_SimulateUIClick(bool* bExtraDoor);
	void ExecuteUbergraph_BP_CommonBtn(int EntryPoint);
};


}

