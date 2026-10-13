#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass MiniTv_Class.MiniTv_Class_C
// 0x0030 (0x05A0 - 0x0570)
class AMiniTv_Class_C : public ALuaActor
{
public:
	struct FPointerToUberGraphFrame UberGraphFrame; // 0x0570(0x0008) (Transient, DuplicateTransient)
	class UCameraComponent* Camera; // 0x0578(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UMinitvAvatarComponent_BP_C* MinitvAvatarComponent_BP; // 0x0580(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class USkeletalMeshComponent* SkeletalMesh; // 0x0588(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UCapsuleComponent* Capsule; // 0x0590(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class USkeletalMeshComponent* PhoneMesh; // 0x0598(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass MiniTv_Class.MiniTv_Class_C");
		return pStaticClass;
	}


	void DestoryPhoneMesh();
	void PlayPhoneAnim();
	void TouchEnd(TEnumAsByte<enum ETouchIndex> Finger);
	void TouchStart(TEnumAsByte<enum ETouchIndex> Finger);
	void UserConstructionScript();
	void BndEvt__SkeletalMesh_K2Node_ComponentBoundEvent_0_ComponentOnInputTouchBeginSignature__DelegateSignature(TEnumAsByte<enum ETouchIndex> FingerIndex, class UPrimitiveComponent* TouchedComponent);
	void BndEvt__SkeletalMesh_K2Node_ComponentBoundEvent_1_ComponentOnInputTouchEndSignature__DelegateSignature(TEnumAsByte<enum ETouchIndex> FingerIndex, class UPrimitiveComponent* TouchedComponent);
	void ReceiveTick(float* DeltaSeconds);
	void ExecuteUbergraph_MiniTv_Class(int EntryPoint);
};


}

