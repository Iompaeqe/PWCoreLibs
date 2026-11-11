// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/SpellParams.h"

#include "GameFramework/GameState.h"
#include "Net/UnrealNetwork.h"


void USpellParams::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	UObject::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(USpellParams, SourcePlayerUniqueId, COND_InitialOnly);
	DOREPLIFETIME_CONDITION(USpellParams, TargetCollisionMask, COND_InitialOnly);
	DOREPLIFETIME_CONDITION(USpellParams, AbilityLevel, COND_InitialOnly);
	DOREPLIFETIME_CONDITION(USpellParams, CastId, COND_InitialOnly);
}

USpellParamsExtension* USpellParams::GetExtensionByClass(TSubclassOf<USpellParamsExtension> ExtensionClass) const
{
	for (const TObjectPtr<USpellParamsExtension>& Ext : Extensions)
	{
		if (Ext && Ext->IsA(ExtensionClass))
			return Ext;
	}
	return nullptr;
}

void USpellParams::OnRep_UniqueId()
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
