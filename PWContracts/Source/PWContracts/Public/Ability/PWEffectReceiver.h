// Copyright (c) 2025 Metehan Goksel Kurtulan (Iompaeqe)

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PWEffectReceiver.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UPWEffectReceiver : public UInterface
{
	GENERATED_BODY()
};

class PWCONTRACTS_API IPWEffectReceiver
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Effects")
	UObject* GetEffectReceiver();
};
