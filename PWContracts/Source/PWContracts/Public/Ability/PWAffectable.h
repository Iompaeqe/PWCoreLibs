// Copyright (c) 2025 Metehan Goksel Kurtulan (Iompaeqe)

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PWAffectable.generated.h"

UINTERFACE(BlueprintType)
class UPWAffectable : public UInterface
{
	GENERATED_BODY()
};

class PWCONTRACTS_API IPWAffectable
{
	GENERATED_BODY()

public:
	// The object that takes effects for an actor, following its IPWEffectReceiver if it has one; null for scenery such as a wall.
	static UObject* Find(AActor* Actor);

	UFUNCTION(BlueprintNativeEvent, Category="Hit")
	bool ApplyEffects(class UPWSpellParams* SpellParams);

	// Ends effects a caster applied earlier. Only receivers that track effects themselves need it.
	UFUNCTION(BlueprintNativeEvent, Category="Hit")
	void RemoveEffects(class UPWSpellParams* SpellParams, bool bInfiniteOnly);
	virtual void RemoveEffects_Implementation(class UPWSpellParams* SpellParams, bool bInfiniteOnly) {}
};
