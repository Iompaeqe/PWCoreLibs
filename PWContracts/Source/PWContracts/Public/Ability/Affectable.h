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
};
