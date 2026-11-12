// Copyright (c) 2025 Metehan Goksel Kurtulan (Iompaeqe)


#include "PWInputConfig.h"

const class UInputAction* UPWInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound)
{
	if (AbilityInputActions.Contains(InputTag))
	{
		return AbilityInputActions[InputTag];
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find InputAction for InputTag [%s] on InputConfig [%s]."), *InputTag.ToString(), *GetNameSafe(this));
	}
	
	return nullptr;
}
