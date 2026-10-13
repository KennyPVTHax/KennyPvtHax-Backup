#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass BP_PlayerTransformComponent.BP_PlayerTransformComponent_C
// 0x0011 (0x0249 - 0x0238)
class UBP_PlayerTransformComponent_C : public ULuaActorComponent
{
public:
	struct FString TransformDataComponentPath; // 0x0238(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	bool bLocalBindCameraSwitch; // 0x0248(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass BP_PlayerTransformComponent.BP_PlayerTransformComponent_C");
		return pStaticClass;
	}

};


}

