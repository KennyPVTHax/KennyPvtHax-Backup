#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass AITouchSelectComp.AITouchSelectComp_C
// 0x0010 (0x0210 - 0x0200)
class UAITouchSelectComp_C : public USTTouchSelectComponent
{
public:
	struct FPointerToUberGraphFrame UberGraphFrame; // 0x0200(0x0008) (Transient, DuplicateTransient)
	struct FVector2D ViewportLocalSize; // 0x0208(0x0008) (Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass AITouchSelectComp.AITouchSelectComp_C");
		return pStaticClass;
	}


	void UpdateViewportLocalSize();
	struct FVector2D ModifyTouchLoc(struct FGeometry* MyGeometry, struct FVector2D* TouchLoc);
	void ReceiveBeginPlay();
	void OnTouchSelect(class AActor* SelectActor, const struct FVector2D& TouchLoc);
	void OnViewPortChange(const struct FVector2D& OldViewportSize, const struct FVector2D& NewViewportSize);
	void ExecuteUbergraph_AITouchSelectComp(int EntryPoint);
};


}

