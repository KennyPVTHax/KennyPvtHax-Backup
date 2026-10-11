#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass CameraSettingComponent.CameraSettingComponent_C
// 0x0014 (0x018C - 0x0178)
class UCameraSettingComponent_C : public UActorComponent
{
public:
	float Current_Target_Arm_Length; // 0x0178(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float CurrentCameraLagSpeed; // 0x017C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FVector CurrentSocketOffset; // 0x0180(0x000C) (Edit, BlueprintVisible, IsPlainOldData)

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass CameraSettingComponent.CameraSettingComponent_C");
		return pStaticClass;
	}


	void SaveCurCameraSetting(class USpringArmComponent* SprintArm);
	void LerpCameraSettings(float LerpAlpha, const struct FSTR_CameraSetting& CameraSettings, class USpringArmComponent* SpringArm);
};


}

