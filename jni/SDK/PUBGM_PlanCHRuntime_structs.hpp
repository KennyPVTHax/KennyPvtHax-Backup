#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Script Structs
//---------------------By BangJO---------------------------

// ScriptStruct PlanCHRuntime.PlanCH_CommonOccupy
// 0x0020
struct FPlanCH_CommonOccupy
{
	int LandId; // 0x0000(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool bOccupied; // 0x0004(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char UnknownData00[0x3]; // 0x0005(0x0003) MISSED OFFSET
	int BeginTime; // 0x0008(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	int EndTime; // 0x000C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FString PlayerUID; // 0x0010(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
};

}

