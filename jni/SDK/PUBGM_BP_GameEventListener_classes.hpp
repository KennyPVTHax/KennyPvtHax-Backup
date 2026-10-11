#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass BP_GameEventListener.BP_GameEventListener_C
// 0x0008 (0x0320 - 0x0318)
class UBP_GameEventListener_C : public UGameEventListener
{
public:
	struct FPointerToUberGraphFrame UberGraphFrame; // 0x0318(0x0008) (Transient, DuplicateTransient)

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass BP_GameEventListener.BP_GameEventListener_C");
		return pStaticClass;
	}


	void SetDefaultNearClipPlane();
	void IsIOSPlatform();
	void SetDefaultRendering();
	void EnableGrassLOD(int Enable);
	void ChangeStreamingLevel();
	void InitIncaseReconnect();
	void ReceiveBeginPlay();
	void ReceiveEndPlay(TEnumAsByte<enum EEndPlayReason>* EndPlayReason);
	void UnloadTree();
	void LoadTree();
	void ExecuteUbergraph_BP_GameEventListener(int EntryPoint);
};


}

