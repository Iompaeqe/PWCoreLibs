// Copyright (c) 2025 Metehan Goksel Kurtulan (Iompaeqe)

#pragma once

#include "LogConfig.h"
#include "LogChannels.h"

#define playername() *UGameplayStatics::GetPlayerController(this, 0)->GetPlayerState<APlayerState>()->GetPlayerName()

#define checkenabled() if(ULogConfig::GetLogConfig()->bDebugFunc)
#define checkifdetailed() if(ULogConfig::GetLogConfig()->bDebugExtraDetails)

#define log(Text) if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::White, TEXT(Text), false)
#define consolelog(Text, ...) UE_LOG(LogTemp, Log, TEXT(Text), ##__VA_ARGS__)
#define logkey(Key, Text) if(GEngine) GEngine->AddOnScreenDebugMessage(Key, 2.f, FColor::White, TEXT(Text))
#define logf(Format, ...) if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::White, FString::Printf(TEXT(Format), ##__VA_ARGS__), false)
#define logkeyf(Key, Format, ...) if(GEngine) GEngine->AddOnScreenDebugMessage(Key, 2.f, FColor::White, FString::Printf(TEXT(Format), ##__VA_ARGS__))
#define lognoformat(String) if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::White, String)

#define logfull(Key, Time, Color, Format, ...) if(GEngine) GEngine->AddOnScreenDebugMessage(Key, Time, Color, FString::Printf(TEXT(Format), ##__VA_ARGS__))
#define logfullnoformat(Key, Time, Color, String) if(GEngine) GEngine->AddOnScreenDebugMessage(Key, Time, Color, String)

#define warn(Text) if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT(Text), false)
#define consolewarn(Text, ...) UE_LOG(LogTemp, Warning, TEXT(Text), ##__VA_ARGS__)
#define warnkey(Key, Text) if(GEngine) GEngine->AddOnScreenDebugMessage(Key, 2.f, FColor::Yellow, TEXT(Text))
#define warnf(Format, ...) if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, FString::Printf(TEXT(Format), ##__VA_ARGS__), false)
#define warnkeyf(Key, Format, ...) if(GEngine) GEngine->AddOnScreenDebugMessage(Key, 2.f, FColor::Yellow, FString::Printf(TEXT(Format), ##__VA_ARGS__))
#define warnnoformat(String) if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, String)

#define error(Text) if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(Text), false)
#define consoleerror(Text, ...) UE_LOG(LogTemp, Error, TEXT(Text), ##__VA_ARGS__)
#define errorkey(Key, Text) if(GEngine) GEngine->AddOnScreenDebugMessage(Key, 2.f, FColor::Red, TEXT(Text))
#define errorf(Format, ...) if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::Printf(TEXT(Format), ##__VA_ARGS__), false)
#define errorkeyf(Key, Format, ...) if(GEngine) GEngine->AddOnScreenDebugMessage(Key, 2.f, FColor::Red, FString::Printf(TEXT(Format), ##__VA_ARGS__))
#define errornoformat(String) if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, String)



/*
	Joy String 
		Current Class, File, and Line Number!
			by 
			
	PreProcessor commands to get 
		a. Class name
		b. Function Name
		c. Line number 
		d. Function Signature (including parameters)
		
	Gives you a UE4 FString anywhere in your code that these macros are used!
	
	Ex: 
		You can use JOYSTR_CUR_CLASS anywhere to get a UE4 FString back telling you 
		what the current class is where you called this macro!
	
	Ex:
		This macro prints the class and line along with the message of your choosing!
		VSCREENMSG("Have fun today!");
	<3  
*/
#pragma once

// Current Class Name + Function Name where this is called!**
#define CUR_CLASS_FUNC (FString(__FUNCTION__))

// Current Class where this is called!**
#define CUR_CLASS (FString(__FUNCTION__).Left(FString(__FUNCTION__).Find(TEXT(":"))))

// Current Function Name where this is called!**
#define CUR_FUNC (FString(__FUNCTION__).Right(FString(__FUNCTION__).Len() - FString(__FUNCTION__).Find(TEXT("::")) - 2))

// Current Line Number in the code where this is called!**
#define CUR_LINE (FString::FromInt(__LINE__))

// Current Class and Line Number where this is called!**
#define CUR_CLASS_LINE (CUR_CLASS + "(" + CUR_LINE + ")")

// Current Function Signature where this is called!**
#define CUR_FUNCSIG (FString(__FUNCSIG__))

// Victory Screen Message
// Gives you the Class name and exact line number where you print a message to yourself!**
#define LOGSCREEN(Param1) (GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *(CUR_CLASS_LINE + ": " + Param1)))

#define LOGSCREEN2(Param1, Param2) (GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *(CUR_CLASS_LINE + ": " + Param1 + " " + Param2)))

#define LOGSCREENF(Param1, Param2) (GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *(CUR_CLASS_LINE + ": " + Param1 + " " + FString::SanitizeFloat(Param2))))

// UE_LOG Messages!
#define logfunc() checkenabled() UE_LOG(LogTemp, Log, TEXT("%s"), *CUR_CLASS_FUNC)
#define warnfunc() checkenabled() UE_LOG(LogTemp, Warning, TEXT("%s"), *CUR_CLASS_FUNC)
#define errorfunc() checkenabled() UE_LOG(LogTemp, Error, TEXT("%s"), *CUR_CLASS_FUNC)
#define logfuncp() checkenabled() UE_LOG(LogTemp, Log, TEXT("Called by: %s - %s"), playername(), *CUR_CLASS_FUNC)
#define warnfuncp() checkenabled() UE_LOG(LogTemp, Warning, TEXT("Called by: %s - %s"), playername(), *CUR_CLASS_FUNC)
#define errorfuncp() checkenabled() UE_LOG(LogTemp, Error, TEXT("Called by: %s - %s"), playername(), *CUR_CLASS_FUNC)
#define logfuncmsg(Param) checkenabled() UE_LOG(LogTemp, Log, TEXT("%s >> %s"), *CUR_CLASS_FUNC, *FString(Param))
#define warnfuncmsg(Param) checkenabled() UE_LOG(LogTemp, Warning, TEXT("%s >> %s"), *CUR_CLASS_FUNC, *FString(Param))
#define errorfuncmsg(Param) checkenabled() UE_LOG(LogTemp, Error, TEXT("%s >> %s"), *CUR_CLASS_FUNC, *FString(Param))
#define logfuncpmsg(Param) checkenabled() UE_LOG(LogTemp, Log, TEXT("Called by: %s - %s >> %s"), playername(), *CUR_CLASS_FUNC, *FString(Param))
#define warnfuncpmsg(Param) checkenabled() UE_LOG(LogTemp, Warning, TEXT("Called by: %s - %s >> %s"), playername(), *CUR_CLASS_FUNC, *FString(Param))
#define errorfuncpmsg(Param) checkenabled() UE_LOG(LogTemp, Error, TEXT("Called by: %s - %s >> %s"), playername(), *CUR_CLASS_FUNC, *FString(Param))
#define logfuncmsgf(Format, ...) checkenabled() UE_LOG(LogTemp, Log, TEXT("%s >> %s"), *CUR_CLASS_FUNC, *FString::Printf(TEXT(Format), ##__VA_ARGS__))
#define warnfuncmsgf(Format, ...) checkenabled() UE_LOG(LogTemp, Warning, TEXT("%s >> %s"), *CUR_CLASS_FUNC, *FString::Printf(TEXT(Format), ##__VA_ARGS__))
#define errorfuncmsgf(Format, ...) checkenabled() UE_LOG(LogTemp, Error, TEXT("%s >> %s"), *CUR_CLASS_FUNC, *FString::Printf(TEXT(Format), ##__VA_ARGS__))
#define logfuncpmsgf(Format, ...) checkenabled() UE_LOG(LogTemp, Log, TEXT("Called by: %s - %s >> %s"), playername(), *CUR_CLASS_FUNC, *FString::Printf(TEXT(Format), ##__VA_ARGS__))
#define warnfuncpmsgf(Format, ...) checkenabled() UE_LOG(LogTemp, Warning, TEXT("Called by: %s - %s >> %s"), playername(), *CUR_CLASS_FUNC, *FString::Printf(TEXT(Format), ##__VA_ARGS__))
#define errorfuncpmsgf(Format, ...) checkenabled() UE_LOG(LogTemp, Error, TEXT("Called by: %s - %s >> %s"), playername(), *CUR_CLASS_FUNC, *FString::Printf(TEXT(Format), ##__VA_ARGS__))

#define logfuncd() checkenabled() checkifdetailed() UE_LOG(LogTemp, Log, TEXT("%s"), *CUR_CLASS_FUNC)
#define logfuncdp() checkenabled() checkifdetailed() UE_LOG(LogTemp, Log, TEXT("Called by: %s - %s"), playername(), *CUR_CLASS_FUNC)
#define logfuncdmsg(Param) checkenabled() checkifdetailed() UE_LOG(LogTemp, Log, TEXT("%s >> %s"), *CUR_CLASS_FUNC, *FString(Param))
#define logfuncdpmsg(Param) checkenabled() checkifdetailed() UE_LOG(LogTemp, Log, TEXT("Called by: %s - %s >> %s"), playername(), *CUR_CLASS_FUNC, *FString(Param))
#define logfuncdmsgf(Format, ...) checkenabled() checkifdetailed() UE_LOG(LogTemp, Log, TEXT("%s >> %s"), *CUR_CLASS_FUNC, *FString::Printf(TEXT(Format), ##__VA_ARGS__))
#define logfuncdpmsgf(Format, ...) checkenabled() checkifdetailed() UE_LOG(LogTemp, Log, TEXT("Called by: %s - %s >> %s"), playername(), *CUR_CLASS_FUNC, *FString::Printf(TEXT(Format), ##__VA_ARGS__))



#define V_LOG(LogCat, Param1) UE_LOG(LogCat, Warning, TEXT("%s: %s"), *LOG_CUR_CLASS_LINE, *FString(Param1))
#define V_LOG2(LogCat, Param1, Param2) UE_LOG(LogCat, Warning, TEXT("%s: %s %s"), *CUR_CLASS_LINE, *FString(Param1), *FString(Param2))
#define V_LOGF(LogCat, Param1, Param2) UE_LOG(LogCat, Warning, TEXT("%s: %s %f"), *CUR_CLASS_LINE, *FString(Param1), Param2)
#define V_LOGM(LogCat, FormatString, ...) UE_LOG(LogCat, Warning, TEXT("%s: %s"), *CUR_CLASS_LINE, *FString::Printf(TEXT(FormatString), ##__VA_ARGS__))
