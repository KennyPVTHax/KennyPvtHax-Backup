#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass GuideComponent_BP.GuideComponent_BP_C
// 0x000D (0x01AD - 0x01A0)
class UGuideComponent_BP_C : public UGuideComponent
{
public:
	struct FPointerToUberGraphFrame UberGraphFrame; // 0x01A0(0x0008) (Transient, DuplicateTransient)
	int guideStep; // 0x01A8(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool Enabled; // 0x01AC(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass GuideComponent_BP.GuideComponent_BP_C");
		return pStaticClass;
	}


	void ShowGuideByStep();
	void AddUIGuide(class UWidget* Widget1, int guildUI1, const struct FVector2D& offset1, const struct FVector2D& size1, int childData1);
	void InitUIGuide();
	void CreateGuideUI();
	void ExecuteUbergraph_GuideComponent_BP(int EntryPoint);
};


}

