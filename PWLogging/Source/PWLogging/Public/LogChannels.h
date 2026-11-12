// Copyright (c) 2025 Metehan Goksel Kurtulan (Iompaeqe)

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "LogChannels.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogProjectW, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogWFunc, Log, All);

DECLARE_LOG_CATEGORY_EXTERN(LogNetwork, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogSpell, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogCharacter, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogPlayer, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogInventory, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogCombat, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogEnvironment, Log, All);

/**
 * 
 */
UCLASS()
class PWLOGGING_API ULogChannels : public UObject
{
	GENERATED_BODY()
};
