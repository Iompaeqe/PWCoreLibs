// Copyright (c) 2025 Metehan Goksel Kurtulan (Iompaeqe)


#include "PWInputRouter.h"

#include "EnhancedInputSubsystems.h"
#include "PWEnhancedInputComponent.h"


void UPWInputRouter::SetMappingContext(const ULocalPlayer* LocalPlayer) const
{
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	if (!Subsystem || !InputConfig) return;
	for (const auto CurrentContext : InputConfig->InputMappingContexts)
	{
		Subsystem->AddMappingContext(CurrentContext, 0);
	}
}

void UPWInputRouter::BindAll(UInputComponent* InputComponent)
{
	UPWEnhancedInputComponent* EIC = CastChecked<UPWEnhancedInputComponent>(InputComponent);
	if (!EIC || !InputConfig) return;
	EIC->BindAbilityActions(InputConfig->AbilityInputActions, this, &ThisClass::HandleTriggered, &ThisClass::HandleStarted, &ThisClass::HandleOngoing, &ThisClass::HandleCanceled, &ThisClass::HandleCompleted);
}
