// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Functions
//---------------------By BangJO---------------------------

// Function CameraSettingComponent.CameraSettingComponent_C.SaveCurCameraSetting
// (Public, BlueprintCallable, BlueprintEvent)
// Parameters:
// class USpringArmComponent* SprintArm (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UCameraSettingComponent_C::SaveCurCameraSetting(class USpringArmComponent* SprintArm)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function CameraSettingComponent.CameraSettingComponent_C.SaveCurCameraSetting");

	UCameraSettingComponent_C_SaveCurCameraSetting_Params params;
	params.SprintArm = SprintArm;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function CameraSettingComponent.CameraSettingComponent_C.LerpCameraSettings
// (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
// Parameters:
// float LerpAlpha (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FSTR_CameraSetting CameraSettings (BlueprintVisible, BlueprintReadOnly, Parm)
// class USpringArmComponent* SpringArm (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UCameraSettingComponent_C::LerpCameraSettings(float LerpAlpha, const struct FSTR_CameraSetting& CameraSettings, class USpringArmComponent* SpringArm)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function CameraSettingComponent.CameraSettingComponent_C.LerpCameraSettings");

	UCameraSettingComponent_C_LerpCameraSettings_Params params;
	params.LerpAlpha = LerpAlpha;
	params.CameraSettings = CameraSettings;
	params.SpringArm = SpringArm;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


}

