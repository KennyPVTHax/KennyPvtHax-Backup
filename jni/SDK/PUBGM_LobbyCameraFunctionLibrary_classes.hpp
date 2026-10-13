#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass LobbyCameraFunctionLibrary.LobbyCameraFunctionLibrary_C
// 0x0000 (0x0090 - 0x0090)
class ULobbyCameraFunctionLibrary_C : public UBlueprintFunctionOverride
{
public:

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass LobbyCameraFunctionLibrary.LobbyCameraFunctionLibrary_C");
		return pStaticClass;
	}


	static void OnViewportSizeChanged(const struct FVector2D& OldViewport, const struct FVector2D& NewViewport, class UObject* __WorldContext);
	static void LevelSequence_ExecuteStartCallback(class UObject* __WorldContext);
	static void GetCurrentCameraActor(class UObject* __WorldContext, class ACameraActor** CameraActor);
	static void LevelSequence_ExecuteEndCallback(class UObject* __WorldContext);
	static void SwitchCamera_Only(int CameraID, float BlendTime, class UObject* __WorldContext);
	static class ULevelSequencePlayer* CreateLevelSequencePlayerAndActor(class ULevelSequence* level_sequence, class UObject* __WorldContext, class ALevelSequenceActor** OutActor);
	static void SwitchCamera(int NewCameraID, float BlendTime, bool IgnoreLight, class UObject* __WorldContext);
};


}

