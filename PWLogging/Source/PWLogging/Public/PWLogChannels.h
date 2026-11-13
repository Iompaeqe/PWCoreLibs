// Copyright (c) 2025 Metehan Goksel Kurtulan (Iompaeqe)

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PWLogChannels.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogProjectW, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogWFunc, Log, All);

DECLARE_LOG_CATEGORY_EXTERN(LogPWNetwork, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogPWSpell, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogPWCharacter, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogPWPlayer, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogPWInventory, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogPWCombat, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogPWEnvironment, Log, All);

UCLASS()
class PWLOGGING_API UPWLogChannels : public UObject
{
	GENERATED_BODY()
};
