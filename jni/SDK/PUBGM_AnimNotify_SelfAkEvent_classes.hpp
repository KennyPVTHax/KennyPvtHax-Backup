#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass AnimNotify_SelfAkEvent.AnimNotify_SelfAkEvent_C
// 0x0000 (0x0081 - 0x0081)
class UAnimNotify_SelfAkEvent_C : public UAnimNotify_AkEvent_C
{
public:

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass AnimNotify_SelfAkEvent.AnimNotify_SelfAkEvent_C");
		return pStaticClass;
	}


	bool PlayAkEvent(class USkeletalMeshComponent* MeshComp);
	bool Received_Notify(class USkeletalMeshComponent** MeshComp, class UAnimSequenceBase** Animation);
};


}

