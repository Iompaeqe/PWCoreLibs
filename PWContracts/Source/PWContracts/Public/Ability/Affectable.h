// Copyright (c) 2025 Metehan Goksel Kurtulan (Iompaeqe)

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Affectable.generated.h"

UINTERFACE(BlueprintType)
class UAffectable : public UInterface
{
	GENERATED_BODY()
};

class PWCONTRACTS_API IAffectable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category="Hit")
	bool ApplyEffects(class USpellParams* SpellParams);

	// Ends effects a caster applied earlier. Only receivers that track effects themselves need it.
	UFUNCTION(BlueprintNativeEvent, Category="Hit")
	void RemoveEffects(class USpellParams* SpellParams, bool bInfiniteOnly);
	virtual void RemoveEffects_Implementation(class USpellParams* SpellParams, bool bInfiniteOnly) {}
};
