#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass Halloween_CarPosition.Halloween_CarPosition_C
// 0x0010 (0x04C0 - 0x04B0)
class AHalloween_CarPosition_C : public AActor
{
public:
	class UArrowComponent* Arrow; // 0x04B0(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class USceneComponent* DefaultSceneRoot; // 0x04B8(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass Halloween_CarPosition.Halloween_CarPosition_C");
		return pStaticClass;
	}


	void UserConstructionScript();
};


}

