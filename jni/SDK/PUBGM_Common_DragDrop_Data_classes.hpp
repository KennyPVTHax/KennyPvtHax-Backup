#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass Common_DragDrop_Data.Common_DragDrop_Data_C
// 0x001C (0x00A4 - 0x0088)
class UCommon_DragDrop_Data_C : public UDragDropOperation
{
public:
	int dragItem; // 0x0088(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char UnknownData00[0x4]; // 0x008C(0x0004) MISSED OFFSET
	struct FString dragExtendData; // 0x0090(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	int dragIndex; // 0x00A0(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass Common_DragDrop_Data.Common_DragDrop_Data_C");
		return pStaticClass;
	}

};


}

