// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MultiDataArray.h"
#include "UObject/Object.h"
#include "SpellParams.generated.h"

class UEffectSpellParamsExtension;

namespace PWParamKeys
{
	static const FName Range = "Range";
	static const FName Radius = "Radius";
}

UENUM(BlueprintType, meta=(Bitflags, UseEnumValuesAsMaskValuesInEditor="true"))
enum class ERelationMask : uint8
{
	None = 0 UMETA(Hidden),
	Self = 1 << 0,
	Ally = 1 << 1,
	Enemy = 1 << 2,
	Neutral = 1 << 3,
	All = Self | Ally | Enemy | Neutral UMETA(Hidden)
};

ENUM_CLASS_FLAGS(ERelationMask)



UCLASS(Abstract, BlueprintType, EditInlineNew)
class PWSHAREDTYPES_API USpellParamsExtension : public UObject
{
	GENERATED_BODY()
};

/**
 * Data carrier object intended to be given to the actors spawn by GA. The data inside can be replicated if the abilities depends it. And the data can be extended via USpellParamsExtension child classes.
 * As is, spellparams and it's required extensions are created for each spell cast, which can be problematic if the game has too many spells being created at the same time.
 * in which case, consider extending the system to pool the spellparams' and it's extensions.
 */
UCLASS(BlueprintType, Blueprintable)
class PWSHAREDTYPES_API USpellParams : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<AActor> SourceAvatar = nullptr;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<AActor> ActorHit = nullptr;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, ReplicatedUsing=OnRep_UniqueId)
	FUniqueNetIdRepl SourcePlayerUniqueId = FUniqueNetIdRepl();
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Replicated)
	float AbilityLevel = 0;


	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Replicated)
	int32 TargetCollisionMask = (int32)ERelationMask::All;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	int32 TargetEffectMask = (int32)ERelationMask::All;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Replicated)
	FGuid CastId;
	
	/**
	 * Modules that need to add **primitive data** to SpellParams can use this container.  
	 * For complex or structured data, see `Extensions`.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Extra")
	TObjectPtr<UMultiDataArray> More = nullptr;
	
	/**
	 * Modules that need to add **complex or structured data** to SpellParams  
	 * should extend `USpellParamsExtension` and use this list to store it.  
	 * For simple or primitive data, see `More`.
	 */
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category="Extra")
	TArray<TObjectPtr<USpellParamsExtension>> Extensions;

	template <typename T>
	T* FindExtension() const
	{
		for (const TObjectPtr<USpellParamsExtension>& Ext : Extensions)
			if (T* AsType = Cast<T>(Ext))
				return AsType;
		return nullptr;
	}

	template <typename T>
	T* AddExtension()
	{
		T* NewExt = NewObject<T>(this);
		Extensions.Add(NewExt);
		return NewExt;
	}

	UFUNCTION()
	virtual void OnRep_UniqueId();
	
	virtual bool IsSupportedForNetworking() const override { return true; }
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION(BlueprintPure, BlueprintPure, Category="Accessors")
	USpellParamsExtension* GetExtensionByClass(TSubclassOf<USpellParamsExtension> ExtensionClass) const;
};
