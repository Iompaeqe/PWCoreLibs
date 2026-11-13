// Copyright (c) 2025 Metehan Goksel Kurtulan (Iompaeqe)

#pragma once

#if PW_WITH_ADVANCED_SESSIONS
  #include "AdvancedSessionsLibrary.h" // gives FSessionsSearchSetting, FSessionPropertyKeyPair, etc.
#endif

#if PW_WITH_OSS
  #include "OnlineSubsystem.h"
  #include "OnlineSubsystemTypes.h" // FVariantData, EOnlineKeyValuePairDataType
#endif

#include "CoreMinimal.h"
#include "JsonObjectConverter.h"
#include "PWLogChannels.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PWDebugLog.generated.h"


UENUM(BlueprintType)
enum class EPWLogCategory : uint8
{
	LogTemp UMETA(DisplayName = "Temp"),
	LogNetwork UMETA(DisplayName = "Network"),
	LogSpell UMETA(DisplayName = "Spell"),
	LogCharacter UMETA(DisplayName = "Character"),
	LogPlayer UMETA(DisplayName = "Player"),
	LogInventory UMETA(DisplayName = "Inventory"),
	LogCombat UMETA(DisplayName = "Combat"),
	LogEnvironment UMETA(DisplayName = "Environment")
};

UCLASS()
class PWLOGGING_API UPWDebugLog : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, CustomThunk, Category = "Debug", meta = (CustomStructureParam = "Property", AdvancedDisplay = "Prefix, Suffix, LogCategory, Tags", AutoCreateRefTerm="Tags"))
	static void LogAsJson(const int32& Property, UObject* WorldContext, const FString& Prefix, const FString& Suffix, EPWLogCategory LogCategory, const TArray<FString>& Tags);

	DECLARE_FUNCTION(execLogAsJson)
	{
		Stack.StepCompiledIn<FProperty>(NULL);
		FProperty* Property = Stack.MostRecentProperty;
		void* ValuePtr = Stack.MostRecentPropertyAddress;

		P_GET_OBJECT(UObject, WorldContext);
		P_GET_PROPERTY(FStrProperty, Prefix);
		P_GET_PROPERTY(FStrProperty, Suffix);
		P_GET_ENUM(EPWLogCategory, LogCategory);
		P_GET_TARRAY(FString, Tags);

		P_FINISH;

		P_NATIVE_BEGIN;
			FString OutputString;
			FString PropertyName = Property->GetNameCPP();

			if (Property->IsA(FEnumProperty::StaticClass()))
			{
				FEnumProperty* EnumProperty = CastField<FEnumProperty>(Property);
				int64 EnumValue = EnumProperty->GetUnderlyingProperty()->GetSignedIntPropertyValue(ValuePtr);
				FString EnumName = EnumProperty->GetEnum()->GetNameStringByValue(EnumValue);
				OutputString = FString::Printf(TEXT("%s%s: %s%s"), *Prefix, *PropertyName, *EnumName, *Suffix);
			}
			else if (Property->IsA(FBoolProperty::StaticClass()))
			{
				bool Value = *static_cast<bool*>(ValuePtr);
				OutputString = FString::Printf(TEXT("%s%s: %ls%s"), *Prefix, *PropertyName, Value ? TEXT("true") : TEXT("false"), *Suffix);
			}
			else if (Property->IsA(FIntProperty::StaticClass()))
			{
				int32 Value = *static_cast<int32*>(ValuePtr);
				OutputString = FString::Printf(TEXT("%s%s: %d%s"), *Prefix, *PropertyName, Value, *Suffix);
			}
			else if (Property->IsA(FFloatProperty::StaticClass()))
			{
				float Value = *static_cast<float*>(ValuePtr);
				OutputString = FString::Printf(TEXT("%s%s: %f%s"), *Prefix, *PropertyName, Value, *Suffix);
			}
			else if (Property->IsA(FStrProperty::StaticClass()))
			{
				FString Value = *static_cast<FString*>(ValuePtr);
				OutputString = FString::Printf(TEXT("%s%s: %s%s"), *Prefix, *PropertyName, *Value, *Suffix);
			}
			else if (Property->IsA(FStructProperty::StaticClass()))
			{
				FStructProperty* StructProperty = CastField<FStructProperty>(Property);
#if PW_WITH_ADVANCED_SESSIONS && PW_WITH_OSS
				if (StructProperty->Struct->GetFName() == FName("SessionsSearchSetting"))
				{
					FSessionsSearchSetting* SessionSearchSetting = static_cast<FSessionsSearchSetting*>(ValuePtr);
					OutputString = FString::Printf(TEXT("%s%s: %s%s"), *Prefix, *PropertyName, *SessionsSearchSettingToJson(SessionSearchSetting), *Suffix);
				}
				else if (StructProperty->Struct->GetFName() == FName("SessionPropertyKeyPair"))
				{
					FSessionPropertyKeyPair* SessionProperty = static_cast<FSessionPropertyKeyPair*>(ValuePtr);
					OutputString = FString::Printf(TEXT("%s%s: %s%s"), *Prefix, *PropertyName, *SessionPropertyKeyPairToJson(SessionProperty), *Suffix);
				}
				else
#endif
				{
					if (FJsonObjectConverter::UStructToJsonObjectString(StructProperty->Struct, ValuePtr, OutputString, 0, 0))
					{
						OutputString = FString::Printf(TEXT("%s%s: %s%s"), *Prefix, *PropertyName, *OutputString, *Suffix);
					}
				}
			}
			else if (Property->IsA(FObjectProperty::StaticClass()))
			{
				UObject* Object = *static_cast<UObject**>(ValuePtr);
				if (FJsonObjectConverter::UStructToJsonObjectString(Object->GetClass(), Object, OutputString, 0, 0))
				{
					OutputString = FString::Printf(TEXT("%s%s: %s%s"), *Prefix, *PropertyName, *OutputString, *Suffix);
				}
			}
			else if (Property->IsA(FArrayProperty::StaticClass()))
			{
				FArrayProperty* ArrayProperty = CastField<FArrayProperty>(Property);
				FScriptArrayHelper ArrayHelper(ArrayProperty, ValuePtr);
				TArray<FString> ArrayElements;
				for (int32 i = 0; i < ArrayHelper.Num(); ++i)
				{
					void* ElementPtr = ArrayHelper.GetRawPtr(i);
					FString ElementString;
					if (ArrayProperty->Inner->IsA(FEnumProperty::StaticClass()))
					{
						FEnumProperty* EnumProperty = CastField<FEnumProperty>(ArrayProperty->Inner);
						int64 EnumValue = EnumProperty->GetUnderlyingProperty()->GetSignedIntPropertyValue(ElementPtr);
						FString EnumName = EnumProperty->GetEnum()->GetNameStringByValue(EnumValue);
						ElementString = FString::Printf(TEXT("%s"), *EnumName);
					}
					else if (ArrayProperty->Inner->IsA(FBoolProperty::StaticClass()))
					{
						bool Value = *static_cast<bool*>(ElementPtr);
						ElementString = FString::Printf(TEXT("%ls"), Value ? TEXT("true") : TEXT("false"));
					}
					else if (ArrayProperty->Inner->IsA(FIntProperty::StaticClass()))
					{
						int32 Value = *static_cast<int32*>(ElementPtr);
						ElementString = FString::Printf(TEXT("%d"), Value);
					}
					else if (ArrayProperty->Inner->IsA(FFloatProperty::StaticClass()))
					{
						float Value = *static_cast<float*>(ElementPtr);
						ElementString = FString::Printf(TEXT("%f"), Value);
					}
					else if (ArrayProperty->Inner->IsA(FStrProperty::StaticClass()))
					{
						FString Value = *static_cast<FString*>(ElementPtr);
						ElementString = Value;
					}
					else if (ArrayProperty->Inner->IsA(FStructProperty::StaticClass()))
					{
						FStructProperty* StructProperty = CastField<FStructProperty>(ArrayProperty->Inner);
#if PW_WITH_ADVANCED_SESSIONS && PW_WITH_OSS
						if (StructProperty->Struct->GetFName() == FName("SessionsSearchSetting"))
						{
							FSessionsSearchSetting* SessionSearchSetting = static_cast<FSessionsSearchSetting*>(ElementPtr);
							ElementString = SessionsSearchSettingToJson(SessionSearchSetting);
						}
						else if (StructProperty->Struct->GetFName() == FName("SessionPropertyKeyPair"))
						{
							FSessionPropertyKeyPair* SessionProperty = static_cast<FSessionPropertyKeyPair*>(ElementPtr);
							ElementString = SessionPropertyKeyPairToJson(SessionProperty);
						}
						else
#endif
						{
							if (FJsonObjectConverter::UStructToJsonObjectString(StructProperty->Struct, ElementPtr, ElementString, 0, 0))
							{
								ElementString = FString::Printf(TEXT("%s"), *ElementString);
							}
						}
					}
					else if (ArrayProperty->Inner->IsA(FObjectProperty::StaticClass()))
					{
						UObject* Object = *static_cast<UObject**>(ElementPtr);
						if (FJsonObjectConverter::UStructToJsonObjectString(Object->GetClass(), Object, ElementString, 0, 0))
						{
							ElementString = FString::Printf(TEXT("%s"), *ElementString);
						}
					}
					else
					{
						ElementString = TEXT("Unsupported element type");
					}
					ArrayElements.Add(ElementString);
				}
				OutputString = FString::Printf(TEXT("%s %s: [\n %s] %s"), *Prefix, *PropertyName, *FString::Join(ArrayElements, TEXT(",\n ")), *Suffix);
			}
			else
			{
				OutputString = FString::Printf(TEXT("%s - %s: Unsupported property type - %s"), *Prefix, *PropertyName, *Suffix);
			}
		
			switch (LogCategory)
			{
			case EPWLogCategory::LogNetwork:
				UE_LOG(LogPWNetwork, Log, TEXT("%s"), *OutputString);
				break;
			case EPWLogCategory::LogSpell:
				UE_LOG(LogPWSpell, Log, TEXT("%s"), *OutputString);
				break;
			case EPWLogCategory::LogCharacter:
				UE_LOG(LogPWCharacter, Log, TEXT("%s"), *OutputString);
				break;
			case EPWLogCategory::LogPlayer:
				UE_LOG(LogPWPlayer, Log, TEXT("%s"), *OutputString);
				break;
			case EPWLogCategory::LogInventory:
				UE_LOG(LogPWInventory, Log, TEXT("%s"), *OutputString);
				break;
			case EPWLogCategory::LogCombat:
				UE_LOG(LogPWCombat, Log, TEXT("%s"), *OutputString);
				break;
			case EPWLogCategory::LogEnvironment:
				UE_LOG(LogPWEnvironment, Log, TEXT("%s"), *OutputString);
				break;
			default:
				UE_LOG(LogTemp, Log, TEXT("%s"), *OutputString);
				break;
			}

		P_NATIVE_END;
	}

private:
#if PW_WITH_ADVANCED_SESSIONS && PW_WITH_OSS
	static FString SessionPropertyKeyPairToJson(const FSessionPropertyKeyPair* SessionProperty)
	{
		TSharedRef<FJsonObject> JsonObject = MakeShareable(new FJsonObject());

		// Add the Key to the JSON object
		JsonObject->SetStringField(TEXT("Key"), SessionProperty->Key.ToString());

		// Manually populate JsonObject with data from VariantData
		const FVariantData* VariantData = &SessionProperty->Data;
		switch (VariantData->GetType())
		{
		case EOnlineKeyValuePairDataType::Int32:
			{
				int32 Value;
				VariantData->GetValue(Value);
				JsonObject->SetNumberField(TEXT("Value"), Value);
				break;
			}
		case EOnlineKeyValuePairDataType::Float:
			{
				float Value;
				VariantData->GetValue(Value);
				JsonObject->SetNumberField(TEXT("Value"), Value);
				break;
			}
		case EOnlineKeyValuePairDataType::String:
			{
				FString Value;
				VariantData->GetValue(Value);
				JsonObject->SetStringField(TEXT("Value"), Value);
				break;
			}
		case EOnlineKeyValuePairDataType::Bool:
			{
				bool Value;
				VariantData->GetValue(Value);
				JsonObject->SetBoolField(TEXT("Value"), Value);
				break;
			}
		default:
			JsonObject->SetStringField(TEXT("Value"), TEXT("Unsupported type"));
			break;
		}

		FString OutputString;
		TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&OutputString);
		FJsonSerializer::Serialize(JsonObject, Writer);

		return OutputString;
	}

	static FString SessionsSearchSettingToJson(FSessionsSearchSetting* SessionsSearchSetting)
	{
		TSharedRef<FJsonObject> JsonObject = MakeShareable(new FJsonObject());

		JsonObject->SetStringField(TEXT("ComparisonOp"), StaticEnum<EOnlineComparisonOpRedux>()->GetNameStringByValue(static_cast<int64>(SessionsSearchSetting->ComparisonOp)));
		JsonObject->SetStringField(TEXT("PropertyKeyPair"), SessionPropertyKeyPairToJson(&SessionsSearchSetting->PropertyKeyPair));

		FString OutputString;
		TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&OutputString);
		FJsonSerializer::Serialize(JsonObject, Writer);

		return OutputString;
	}
#endif
	
};
