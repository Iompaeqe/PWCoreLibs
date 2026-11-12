// Copyright (c) 2025 Metehan Goksel Kurtulan (Iompaeqe)

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "PWInputRouter.generated.h"

class UInputMappingContext;
class UPWInputConfig;
class UPWEnhancedInputComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPWOnInputTagEvent, const FGameplayTag&, InputTag);

UCLASS(ClassGroup=(Input), meta=(BlueprintSpawnableComponent))
class PWINPUT_API UPWInputRouter : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UPWInputConfig* InputConfig = nullptr;

	UPROPERTY(BlueprintAssignable)
	FPWOnInputTagEvent OnTriggered;
	UPROPERTY(BlueprintAssignable)
	FPWOnInputTagEvent OnStarted;
	UPROPERTY(BlueprintAssignable)
	FPWOnInputTagEvent OnOngoing;
	UPROPERTY(BlueprintAssignable)
	FPWOnInputTagEvent OnCanceled;
	UPROPERTY(BlueprintAssignable)
	FPWOnInputTagEvent OnCompleted;

	void SetMappingContext(const ULocalPlayer* LocalPlayer) const;
	void BindAll(UInputComponent* InputComponent);

	UFUNCTION()
	virtual void HandleTriggered(const FGameplayTag Tag) { OnTriggered.Broadcast(Tag); }
	UFUNCTION()
	virtual void HandleStarted(const FGameplayTag Tag) { OnStarted.Broadcast(Tag); }
	UFUNCTION()
	virtual void HandleOngoing(const FGameplayTag Tag) { OnOngoing.Broadcast(Tag); }
	UFUNCTION()
	virtual void HandleCanceled(const FGameplayTag Tag) { OnCanceled.Broadcast(Tag); }
	UFUNCTION()
	virtual void HandleCompleted(const FGameplayTag Tag) { OnCompleted.Broadcast(Tag); }
};
