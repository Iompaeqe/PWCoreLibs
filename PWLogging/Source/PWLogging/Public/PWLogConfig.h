// Copyright (c) 2025 Metehan Goksel Kurtulan (Iompaeqe)

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PWLogConfig.generated.h"

UCLASS(Config=Game, Blueprintable, DefaultConfig)
class PWLOGGING_API UPWLogConfig : public UObject
{
	GENERATED_BODY()
public:
	UPWLogConfig()
	{
		LoadConfig();
	}
	
	UFUNCTION(BlueprintCallable, Category = "Debug")
	static UPWLogConfig* GetLogConfig();
	
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
