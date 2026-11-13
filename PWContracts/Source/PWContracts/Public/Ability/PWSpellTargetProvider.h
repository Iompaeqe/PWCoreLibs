// Copyright (c) 2025 Metehan Goksel Kurtulan (Iompaeqe)

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PWSpellTargetProvider.generated.h"

class USpellParams;

UINTERFACE(meta=(CannotImplementInterfaceInBlueprint))
class UPWSpellTargetProvider : public UInterface
{
	GENERATED_BODY()
};

// Tells a spawned spell actor who its impact affects, without the actor knowing how the ability picks targets.
class PWCONTRACTS_API IPWSpellTargetProvider
{
	GENERATED_BODY()

public:
	// The impact is where SpellActor is now; Hit carries what it touched, if anything.
	virtual void GetImpactTargets(const AActor* SpellActor, const USpellParams* Params, const FHitResult& Hit, TArray<AActor*>& OutTargets) const = 0;
};
