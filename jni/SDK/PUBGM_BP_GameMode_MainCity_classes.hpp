#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass BP_GameMode_MainCity.BP_GameMode_MainCity_C
// 0x0008 (0x2338 - 0x2330)
class ABP_GameMode_MainCity_C : public AMainCityGameMode
{
public:
	class USceneComponent* DefaultSceneRoot; // 0x2330(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass BP_GameMode_MainCity.BP_GameMode_MainCity_C");
		return pStaticClass;
	}


	void UserConstructionScript();
};


}

