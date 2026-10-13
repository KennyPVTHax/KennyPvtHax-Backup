#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass ShineInterface.ShineInterface_C
// 0x0000 (0x0028 - 0x0028)
class UShineInterface_C : public UInterface
{
public:

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass ShineInterface.ShineInterface_C");
		return pStaticClass;
	}


	void ShowNormal();
	void ShowShine();
};


}

