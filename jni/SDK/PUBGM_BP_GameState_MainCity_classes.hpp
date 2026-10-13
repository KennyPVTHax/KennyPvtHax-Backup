#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass BP_GameState_MainCity.BP_GameState_MainCity_C
// 0x0010 (0x1648 - 0x1638)
class ABP_GameState_MainCity_C : public AMainCityGameState
{
public:
	class USceneComponent* DefaultSceneRoot; // 0x1638(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class ULevelDynamicComponent* LevelDynamic; // 0x1640(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass BP_GameState_MainCity.BP_GameState_MainCity_C");
		return pStaticClass;
	}


	void MulticastRPC_SwitchDS(uint64_t MulticastRPC_SwitchDS_param1);
	void MultiCast_GenericRPC(int MultiCast_GenericRPC_param1, class UObject* MultiCast_GenericRPC_param2, TArray<unsigned char> MultiCast_GenericRPC_param3);
	void __FeatureRPC_ReviveState_MulticastRevivalTimeEnd__();
	void __FeatureRPC_FatalDamageFeature_MulticastRPC_BroadcastFatalDamageToClientForLua__(const struct FFatalDamageParameterCompress& __FeatureRPC_FatalDamageFeature_MulticastRPC_BroadcastFatalDamageToClientForLua___param1, TArray<unsigned char> __FeatureRPC_FatalDamageFeature_MulticastRPC_BroadcastFatalDamageToClientForLua___param2);
	void UserConstructionScript();
};


}

