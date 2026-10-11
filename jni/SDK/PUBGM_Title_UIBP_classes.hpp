#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// WidgetBlueprintGeneratedClass Title_UIBP.Title_UIBP_C
// 0x0010 (0x02D8 - 0x02C8)
class UTitle_UIBP_C : public ULuaUserWidget
{
public:
	struct FPointerToUberGraphFrame UberGraphFrame; // 0x02C8(0x0008) (Transient, DuplicateTransient)
	class UCanvasPanel* CanvasPanelRoot; // 0x02D0(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("WidgetBlueprintGeneratedClass Title_UIBP.Title_UIBP_C");
		return pStaticClass;
	}


	void SetAliasInfo(int ID, const struct FString& Title, const struct FString& Nation, float Available_len, int RankID);
	void PreConstruct(bool* IsDesignTime);
	void ExecuteUbergraph_Title_UIBP(int EntryPoint);
};


}

