// Copyright (c) 2025 Metehan Goksel Kurtulan (Iompaeqe)

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PWMultiDataArray.generated.h"

USTRUCT(BlueprintType)
struct PWSHAREDTYPES_API FPWMultiDataValue
{
	GENERATED_BODY()

	UPROPERTY()
	FString StringValue;

	UPROPERTY()
	float FloatValue;

	UPROPERTY()
	FVector VectorValue;

	UPROPERTY()
	int32 IntValue;

	UPROPERTY()
	bool BoolValue;

	FPWMultiDataValue(): FloatValue(0), VectorValue(FVector::ZeroVector), IntValue(0), BoolValue(false)
	{
	}
};

UCLASS(BlueprintType, Blueprintable)
class PWSHAREDTYPES_API UPWMultiDataArray : public UObject
{
	GENERATED_BODY()

public:
	UPWMultiDataArray();
	
	UPROPERTY(BlueprintReadWrite)
	TMap<FString, FPWMultiDataValue> Data;

	UFUNCTION(BlueprintCallable)
	void AddString(const FString& Key, const FString& Value)
	{
		FPWMultiDataValue DataValue;
		DataValue.StringValue = Value;
		Data.Add(Key, DataValue);
	}

	UFUNCTION(BlueprintCallable)
	void AddFloat(const FString& Key, float Value)
	{
		FPWMultiDataValue DataValue;
		DataValue.FloatValue = Value;
		Data.Add(Key, DataValue);
	}

	UFUNCTION(BlueprintCallable)
	void AddVector(const FString& Key, const FVector& Value)
	{
		FPWMultiDataValue DataValue;
		DataValue.VectorValue = Value;
		Data.Add(Key, DataValue);
	}

	UFUNCTION(BlueprintCallable)
	void AddInt(const FString& Key, int32 Value)
	{
		FPWMultiDataValue DataValue;
		DataValue.IntValue = Value;
		Data.Add(Key, DataValue);
	}

	UFUNCTION(BlueprintCallable)
	void AddBool(const FString& Key, bool Value)
	{
		FPWMultiDataValue DataValue;
		DataValue.BoolValue = Value;
		Data.Add(Key, DataValue);
	}

	UFUNCTION(BlueprintCallable)
	FString GetString(const FString& Key) const
	{
		return Data.Contains(Key) ? Data[Key].StringValue : FString();
	}

	UFUNCTION(BlueprintCallable)
	float GetFloat(const FString& Key) const
	{
		return Data.Contains(Key) ? Data[Key].FloatValue : 0.0f;
	}

	UFUNCTION(BlueprintCallable)
	FVector GetVector(const FString& Key) const
	{
		return Data.Contains(Key) ? Data[Key].VectorValue : FVector::ZeroVector;
	}

	UFUNCTION(BlueprintCallable)
	int32 GetInt(const FString& Key) const
	{
		return Data.Contains(Key) ? Data[Key].IntValue : 0;
	}

	UFUNCTION(BlueprintCallable)
	bool GetBool(const FString& Key) const
	{
		return Data.Contains(Key) ? Data[Key].BoolValue : false;
	}
};
