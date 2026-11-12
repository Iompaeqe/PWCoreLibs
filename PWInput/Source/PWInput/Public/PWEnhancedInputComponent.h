// Copyright (c) 2025 Metehan Goksel Kurtulan (Iompaeqe)

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "PWInputConfig.h"
#include "PWEnhancedInputComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PWINPUT_API UPWEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:

	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityActions(const TMap<FGameplayTag, TObjectPtr<UInputAction>> AbilityInputActions, UserClass* Object, PressedFuncType TriggeredFunc, ReleasedFuncType StartedFunc, HeldFuncType OngoingFunc, HeldFuncType CanceledFunc, HeldFuncType CompletedFunc);
};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UPWEnhancedInputComponent::BindAbilityActions(const TMap<FGameplayTag, TObjectPtr<UInputAction>> AbilityInputActions, UserClass* Object, PressedFuncType TriggeredFunc, ReleasedFuncType StartedFunc, HeldFuncType OngoingFunc, HeldFuncType CanceledFunc, HeldFuncType CompletedFunc)
{
	for (auto& Action : AbilityInputActions)
	{
		if (Action.Value && Action.Key.IsValid())
		{
			if (TriggeredFunc)
			{
				BindAction(Action.Value, ETriggerEvent::Triggered, Object, TriggeredFunc, Action.Key);
			}
			if (StartedFunc)
			{
				BindAction(Action.Value, ETriggerEvent::Started, Object, StartedFunc, Action.Key);
			}
			if (OngoingFunc)
			{
				BindAction(Action.Value, ETriggerEvent::Ongoing, Object, OngoingFunc, Action.Key);
			}
			if (CanceledFunc)
			{
				BindAction(Action.Value, ETriggerEvent::Canceled, Object, CanceledFunc, Action.Key);
			}
			if (CompletedFunc)
			{
				BindAction(Action.Value, ETriggerEvent::Completed, Object, CompletedFunc, Action.Key);
			}
		}
	} 
}

