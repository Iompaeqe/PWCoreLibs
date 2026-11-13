// Copyright (c) 2025 Metehan Goksel Kurtulan (Iompaeqe)

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SpellCollision.generated.h"

// On a spell actor: it collides with nothing.
UINTERFACE()
class UNoCollision : public UInterface
{
	GENERATED_BODY()
};

class PWCONTRACTS_API INoCollision
{
	GENERATED_BODY()
};

// On an actor or a component: spell actors pass through it without triggering their impact.
UINTERFACE()
class UDontTriggerCollision : public UInterface
{
	GENERATED_BODY()
};

class PWCONTRACTS_API IDontTriggerCollision
{
	GENERATED_BODY()
};
