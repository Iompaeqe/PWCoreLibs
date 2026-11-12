// Copyright (c) 2025 Metehan Goksel Kurtulan (Iompaeqe)

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "LogConfig.generated.h"

UCLASS(Config=Game, Blueprintable, DefaultConfig)
class PWLOGGING_API ULogConfig : public UObject
{
	GENERATED_BODY()
public:
	ULogConfig()
	{
		LoadConfig();
	}
	
	UFUNCTION(BlueprintCallable, Category = "Debug")
	static ULogConfig* GetLogConfig();
	
	// Enables the function-name logging macros.
	UPROPERTY(EditAnywhere, Config, BlueprintReadOnly, Category = "Debug Settings")
	bool bDebugFunc = true;

	// Enables economy logging.
	UPROPERTY(EditAnywhere, Config, BlueprintReadOnly, Category = "Debug Settings")
	bool bDebugEconomy = true;

	// Enables the extra-detail logging macros.
	UPROPERTY(EditAnywhere, Config, BlueprintReadOnly, Category = "Debug Settings")
	bool bDebugExtraDetails = true;
	
};
