// Copyright (c) 2025 Metehan Goksel Kurtulan (Iompaeqe)


#include "Ability/PWSpellParams.h"

#include "GameFramework/GameState.h"
#include "Net/UnrealNetwork.h"


void UPWSpellParams::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	UObject::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UPWSpellParams, SourcePlayerUniqueId, COND_InitialOnly);
	DOREPLIFETIME_CONDITION(UPWSpellParams, TargetCollisionMask, COND_InitialOnly);
	DOREPLIFETIME_CONDITION(UPWSpellParams, AbilityLevel, COND_InitialOnly);
	DOREPLIFETIME_CONDITION(UPWSpellParams, CastId, COND_InitialOnly);
}

UPWSpellParamsExtension* UPWSpellParams::GetExtensionByClass(TSubclassOf<UPWSpellParamsExtension> ExtensionClass) const
{
	for (const TObjectPtr<UPWSpellParamsExtension>& Ext : Extensions)
	{
		if (Ext && Ext->IsA(ExtensionClass))
			return Ext;
	}
	return nullptr;
}

void UPWSpellParams::OnRep_UniqueId()
{
	const UObject* Outer = GetOuter();
	const UWorld* World = Outer->GetWorld();
	const AGameState* GameState = World->GetGameState<AGameState>();
	// if (APlayerState* PlayerState = Cast<APlayerState>(Cast<INetIdInterface>(GameState)->GetPlayerStateFromUniqueNetId(UniqueId)))
	// {
	// 	SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(PlayerState);
	// 	if (PlayerState->GetPawn())
	// 		SourceAvatar = PlayerState->GetPawn();
	// }
}
