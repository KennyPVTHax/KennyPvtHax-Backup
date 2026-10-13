#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// Class PixUICanvas.PixCanvasMgr
// 0x0000 (0x0028 - 0x0028)
class UPixCanvasMgr : public UObject
{
public:

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class PixUICanvas.PixCanvasMgr");
		return pStaticClass;
	}

};


}

