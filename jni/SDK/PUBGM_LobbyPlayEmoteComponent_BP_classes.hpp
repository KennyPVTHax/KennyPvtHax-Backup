#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass LobbyPlayEmoteComponent_BP.LobbyPlayEmoteComponent_BP_C
// 0x0072 (0x0652 - 0x05E0)
class ULobbyPlayEmoteComponent_BP_C : public ULobbyPlayEmoteComponent
{
public:
	struct FPointerToUberGraphFrame UberGraphFrame; // 0x05E0(0x0008) (Transient, DuplicateTransient)
	class ULevelSequencePlayer* LevelSequencePlayer; // 0x05E8(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class ALevelSequenceActor* LevelSequenceActor; // 0x05F0(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance, IsPlainOldData)
	class UUserWidget* levelSequenceMask; // 0x05F8(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char UnknownData00[0x50]; // 0x0600(0x0050) UNKNOWN PROPERTY: SetProperty LobbyPlayEmoteComponent_BP.LobbyPlayEmoteComponent_BP_C.stopEmoteArray
	bool bFreezeEndFrame; // 0x0650(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool bUseSequenceCamera; // 0x0651(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass LobbyPlayEmoteComponent_BP.LobbyPlayEmoteComponent_BP_C");
		return pStaticClass;
	}


	void OnEquipmentChange(int resID, bool bPutOn);
	void OnStartLevelSequence();
	void GetLobbyCamera(class ACameraActor** CameraActor);
	void OnStopLevelSequence();
	void ChangetoLevelSequenceCamera();
	void OnTrackEvent(const struct FString& EventData);
	void PlayCameraEmoteAnim(class ULevelSequence** CurrentCameraEmoteAnim);
	void StopCameraEmoteAnim();
	void ShowAvatarForEmote(bool* Show, bool* Force);
	void BindEventToCameraSequence(class ULevelSequencePlayer** SeqPlayer);
	void ExecuteUbergraph_LobbyPlayEmoteComponent_BP(int EntryPoint);
};


}

