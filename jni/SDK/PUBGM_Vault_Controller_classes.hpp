#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass Vault_Controller.Vault_Controller_C
// 0x0008 (0x0AB8 - 0x0AB0)
class UVault_Controller_C : public UPlayerMantleComponent
{
public:
	struct FPointerToUberGraphFrame UberGraphFrame; // 0x0AB0(0x0008) (Transient, DuplicateTransient)

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass Vault_Controller.Vault_Controller_C");
		return pStaticClass;
	}


	void JumpVault();
	void VaultServer(float dis, float Height, float Length, const struct FString& VaultKey, const struct FVector& StartPos, class AActor* checkActor, float crossblockMaxFall, float crossblockMaxDis, const struct FVector& HitPoint, class AActor* WindowActor, const struct FRotator& MoveDir);
	void vaultAll(float dis, float Height, float Length, const struct FString& VaultKey, const struct FVector& StartPos, class AActor* checkActor, float crossmaxFalling, float crossmaxDis, const struct FVector& HitPoint, const struct FRotator& MoveDir);
	void StopVault();
	void DsCheckStopVault();
	void ExecuteUbergraph_Vault_Controller(int EntryPoint);
};


}

