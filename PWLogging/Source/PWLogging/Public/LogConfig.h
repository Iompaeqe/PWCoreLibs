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
	
	UPROPERTY(EditAnywhere, Config, BlueprintReadOnly, Category = "Debug Settings")
	bool bDebugFunc = true;

	UPROPERTY(EditAnywhere, Config, BlueprintReadOnly, Category = "Debug Settings")
	bool bDebugEconomy = true;

	UPROPERTY(EditAnywhere, Config, BlueprintReadOnly, Category = "Debug Settings")
	bool bDebugExtraDetails = true;
	
};
