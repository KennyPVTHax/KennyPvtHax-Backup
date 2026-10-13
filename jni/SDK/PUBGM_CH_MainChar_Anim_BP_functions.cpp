// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Functions
//---------------------By BangJO---------------------------

// Function CH_MainChar_Anim_BP.CH_MainChar_Anim_BP_C.EvaluateGraphExposedInputs_ExecuteUbergraph_CH_MainChar_Anim_BP_AnimGraphNode_BlendListByBool_2E47FBFF49F72ABC9D5C60B35FCBF042
// (BlueprintEvent)

void UCH_MainChar_Anim_BP_C::EvaluateGraphExposedInputs_ExecuteUbergraph_CH_MainChar_Anim_BP_AnimGraphNode_BlendListByBool_2E47FBFF49F72ABC9D5C60B35FCBF042()
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function CH_MainChar_Anim_BP.CH_MainChar_Anim_BP_C.EvaluateGraphExposedInputs_ExecuteUbergraph_CH_MainChar_Anim_BP_AnimGraphNode_BlendListByBool_2E47FBFF49F72ABC9D5C60B35FCBF042");

	UCH_MainChar_Anim_BP_C_EvaluateGraphExposedInputs_ExecuteUbergraph_CH_MainChar_Anim_BP_AnimGraphNode_BlendListByBool_2E47FBFF49F72ABC9D5C60B35FCBF042_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function CH_MainChar_Anim_BP.CH_MainChar_Anim_BP_C.ExecuteUbergraph_CH_MainChar_Anim_BP
// ()
// Parameters:
// int EntryPoint (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UCH_MainChar_Anim_BP_C::ExecuteUbergraph_CH_MainChar_Anim_BP(int EntryPoint)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function CH_MainChar_Anim_BP.CH_MainChar_Anim_BP_C.ExecuteUbergraph_CH_MainChar_Anim_BP");

	UCH_MainChar_Anim_BP_C_ExecuteUbergraph_CH_MainChar_Anim_BP_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


}

