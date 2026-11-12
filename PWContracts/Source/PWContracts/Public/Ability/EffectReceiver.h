// Copyright (c) 2025 Metehan Goksel Kurtulan (Iompaeqe)

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EffectReceiver.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UEffectReceiver : public UInterface
{
	GENERATED_BODY()
};

class PWCONTRACTS_API IEffectReceiver
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Effects")
	UObject* GetEffectReceiver();
};
