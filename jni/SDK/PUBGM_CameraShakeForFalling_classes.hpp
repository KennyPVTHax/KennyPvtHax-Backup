#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass CameraShakeForFalling.CameraShakeForFalling_C
// 0x0008 (0x0168 - 0x0160)
class UCameraShakeForFalling_C : public UCameraShake
{
public:
	struct FPointerToUberGraphFrame UberGraphFrame; // 0x0160(0x0008) (Transient, DuplicateTransient)

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass CameraShakeForFalling.CameraShakeForFalling_C");
		return pStaticClass;
	}


	void ReceivePlayShake(float* Scale);
	void ExecuteUbergraph_CameraShakeForFalling(int EntryPoint);
};


}

