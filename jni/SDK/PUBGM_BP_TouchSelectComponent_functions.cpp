// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Functions
//---------------------By BangJO---------------------------

// Function BP_TouchSelectComponent.BP_TouchSelectComponent_C.RefreshViewportSize
// (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
// Parameters:
// struct FVector2D OldSize (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FVector2D NewSize (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)

void UBP_TouchSelectComponent_C::RefreshViewportSize(const struct FVector2D& OldSize, const struct FVector2D& NewSize)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function BP_TouchSelectComponent.BP_TouchSelectComponent_C.RefreshViewportSize");

	UBP_TouchSelectComponent_C_RefreshViewportSize_Params params;
	params.OldSize = OldSize;
	params.NewSize = NewSize;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function BP_TouchSelectComponent.BP_TouchSelectComponent_C.ModifyTouchLoc
// (Event, Protected, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
// Parameters:
// struct FGeometry MyGeometry (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, IsPlainOldData)
// struct FVector2D TouchLoc (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, IsPlainOldData)
// struct FVector2D ReturnValue (Parm, OutParm, ReturnParm, IsPlainOldData)

struct FVector2D UBP_TouchSelectComponent_C::ModifyTouchLoc(struct FGeometry* MyGeometry, struct FVector2D* TouchLoc)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function BP_TouchSelectComponent.BP_TouchSelectComponent_C.ModifyTouchLoc");

	UBP_TouchSelectComponent_C_ModifyTouchLoc_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	if (MyGeometry != nullptr)
		*MyGeometry = params.MyGeometry;
	if (TouchLoc != nullptr)
		*TouchLoc = params.TouchLoc;

	return params.ReturnValue;
}


// Function BP_TouchSelectComponent.BP_TouchSelectComponent_C.ReceiveBeginPlay
// (Event, Public, BlueprintEvent)

void UBP_TouchSelectComponent_C::ReceiveBeginPlay()
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function BP_TouchSelectComponent.BP_TouchSelectComponent_C.ReceiveBeginPlay");

	UBP_TouchSelectComponent_C_ReceiveBeginPlay_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function BP_TouchSelectComponent.BP_TouchSelectComponent_C.ExecuteUbergraph_BP_TouchSelectComponent
// ()
// Parameters:
// int EntryPoint (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_TouchSelectComponent_C::ExecuteUbergraph_BP_TouchSelectComponent(int EntryPoint)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function BP_TouchSelectComponent.BP_TouchSelectComponent_C.ExecuteUbergraph_BP_TouchSelectComponent");

	UBP_TouchSelectComponent_C_ExecuteUbergraph_BP_TouchSelectComponent_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


}

