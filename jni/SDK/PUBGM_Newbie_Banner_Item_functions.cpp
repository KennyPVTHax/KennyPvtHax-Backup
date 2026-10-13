// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Functions
//---------------------By BangJO---------------------------

// Function Newbie_Banner_Item.Newbie_Banner_Item_C.ItemClickDispatcher__DelegateSignature
// (Public, Delegate, BlueprintCallable, BlueprintEvent)
// Parameters:
// class ULobby_Activity_BtnItem_C* Item (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UNewbie_Banner_Item_C::ItemClickDispatcher__DelegateSignature(class ULobby_Activity_BtnItem_C* Item)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Newbie_Banner_Item.Newbie_Banner_Item_C.ItemClickDispatcher__DelegateSignature");

	UNewbie_Banner_Item_C_ItemClickDispatcher__DelegateSignature_Params params;
	params.Item = Item;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Newbie_Banner_Item.Newbie_Banner_Item_C.ItemMoveRightDispatcher__DelegateSignature
// (Public, Delegate, BlueprintCallable, BlueprintEvent)
// Parameters:
// class ULobby_Activity_BtnItem_C* Item (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UNewbie_Banner_Item_C::ItemMoveRightDispatcher__DelegateSignature(class ULobby_Activity_BtnItem_C* Item)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Newbie_Banner_Item.Newbie_Banner_Item_C.ItemMoveRightDispatcher__DelegateSignature");

	UNewbie_Banner_Item_C_ItemMoveRightDispatcher__DelegateSignature_Params params;
	params.Item = Item;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Newbie_Banner_Item.Newbie_Banner_Item_C.ItemMoveLeftDispatcher__DelegateSignature
// (Public, Delegate, BlueprintCallable, BlueprintEvent)
// Parameters:
// class ULobby_Activity_BtnItem_C* Item (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UNewbie_Banner_Item_C::ItemMoveLeftDispatcher__DelegateSignature(class ULobby_Activity_BtnItem_C* Item)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Newbie_Banner_Item.Newbie_Banner_Item_C.ItemMoveLeftDispatcher__DelegateSignature");

	UNewbie_Banner_Item_C_ItemMoveLeftDispatcher__DelegateSignature_Params params;
	params.Item = Item;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


}

