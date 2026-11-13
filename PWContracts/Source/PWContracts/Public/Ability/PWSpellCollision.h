// Copyright (c) 2025 Metehan Goksel Kurtulan (Iompaeqe)

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PWSpellCollision.generated.h"

// On a spell actor: it collides with nothing.
UINTERFACE()
class UPWNoCollision : public UInterface
{
	GENERATED_BODY()
};

class PWCONTRACTS_API IPWNoCollision
{
	GENERATED_BODY()
};

// On an actor or a component: spell actors pass through it without triggering their impact.
UINTERFACE()
class UPWDontTriggerCollision : public UInterface
{
	GENERATED_BODY()
};

class PWCONTRACTS_API IPWDontTriggerCollision
{
	GENERATED_BODY()
};
