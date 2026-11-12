// Copyright (c) 2025 Metehan Goksel Kurtulan (Iompaeqe)

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "PWInputConfig.generated.h"

class UInputMappingContext;
UCLASS()
class PWINPUT_API UPWInputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	const class UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound);
		
	UPROPERTY(EditDefaultsOnly)
	TArray<TObjectPtr<UInputMappingContext>> InputMappingContexts;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<FGameplayTag, TObjectPtr<UInputAction>> AbilityInputActions;
};
