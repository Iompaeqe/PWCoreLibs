// Copyright (c) 2025 Metehan Goksel Kurtulan (Iompaeqe)

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MultiDataArray.generated.h"

USTRUCT(BlueprintType)
struct PWSHAREDTYPES_API FMultiDataValue
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

	FMultiDataValue(): FloatValue(0), VectorValue(FVector::ZeroVector), IntValue(0), BoolValue(false)
	{
	}
};

UCLASS(BlueprintType, Blueprintable)
class PWSHAREDTYPES_API UMultiDataArray : public UObject
{
	GENERATED_BODY()

public:
	UMultiDataArray();
	
	UPROPERTY(BlueprintReadWrite)
	TMap<FString, FMultiDataValue> Data;

	UFUNCTION(BlueprintCallable)
	void AddString(const FString& Key, const FString& Value)
	{
		FMultiDataValue DataValue;
		DataValue.StringValue = Value;
		Data.Add(Key, DataValue);
	}

	UFUNCTION(BlueprintCallable)
	void AddFloat(const FString& Key, float Value)
	{
		FMultiDataValue DataValue;
		DataValue.FloatValue = Value;
		Data.Add(Key, DataValue);
	}

	UFUNCTION(BlueprintCallable)
	void AddVector(const FString& Key, const FVector& Value)
	{
		FMultiDataValue DataValue;
		DataValue.VectorValue = Value;
		Data.Add(Key, DataValue);
	}

	UFUNCTION(BlueprintCallable)
	void AddInt(const FString& Key, int32 Value)
	{
		FMultiDataValue DataValue;
		DataValue.IntValue = Value;
		Data.Add(Key, DataValue);
	}

	UFUNCTION(BlueprintCallable)
	void AddBool(const FString& Key, bool Value)
	{
		FMultiDataValue DataValue;
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
