#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass BP_MiniTVSpline.BP_MiniTVSpline_C
// 0x0009 (0x04B9 - 0x04B0)
class ABP_MiniTVSpline_C : public AActor
{
public:
	class USplineComponent* Spline; // 0x04B0(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool MoveActor; // 0x04B8(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass BP_MiniTVSpline.BP_MiniTVSpline_C");
		return pStaticClass;
	}


	void UserConstructionScript();
};


}

