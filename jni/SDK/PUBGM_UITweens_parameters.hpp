#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Parameters
//---------------------By BangJO---------------------------

// Function UITweens.TweenManager.TweenScale
struct UTweenManager_TweenScale_Params
{
	class UWidget* Widget; // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FVector2D From; // (Parm, IsPlainOldData)
	struct FVector2D To; // (Parm, IsPlainOldData)
	float Timespan; // (Parm, ZeroConstructor, IsPlainOldData)
	int Type; // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function UITweens.TweenManager.TweenPosition
struct UTweenManager_TweenPosition_Params
{
	class UWidget* Widget; // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FVector2D From; // (Parm, IsPlainOldData)
	struct FVector2D To; // (Parm, IsPlainOldData)
	float Timespan; // (Parm, ZeroConstructor, IsPlainOldData)
	int Type; // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function UITweens.TweenManager.TweenAlpha
struct UTweenManager_TweenAlpha_Params
{
	class UWidget* Widget; // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	float From; // (Parm, ZeroConstructor, IsPlainOldData)
	float To; // (Parm, ZeroConstructor, IsPlainOldData)
	float Timespan; // (Parm, ZeroConstructor, IsPlainOldData)
	int Type; // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function UITweens.TweenManager.Tick
struct UTweenManager_Tick_Params
{
	float DeltaTime; // (Parm, ZeroConstructor, IsPlainOldData)
};

}

