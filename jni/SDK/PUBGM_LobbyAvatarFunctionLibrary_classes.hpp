#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass LobbyAvatarFunctionLibrary.LobbyAvatarFunctionLibrary_C
// 0x0000 (0x0090 - 0x0090)
class ULobbyAvatarFunctionLibrary_C : public UBlueprintFunctionOverride
{
public:

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass LobbyAvatarFunctionLibrary.LobbyAvatarFunctionLibrary_C");
		return pStaticClass;
	}


	static void OnPlayerRotate(class UCharacterAvatarComp2_BP_C* AvatarComp, class UObject* __WorldContext);
};


}

