// Copyright (c) 2025 Metehan Goksel Kurtulan (Iompaeqe)

#pragma once

#include "TimerManager.h"
#include "Engine/World.h"
#include "CoreMinimal.h"

// Declare a timer handle
#define DECLARE_TIMER(Name) FTimerHandle Name##TimerHandle;

// Clear a timer safely
#define CLEAR_TIMER(Name) \
    if (GetWorld() && Name##TimerHandle.IsValid()) \
    { \
        GetWorld()->GetTimerManager().ClearTimer(Name##TimerHandle); \
        Name##TimerHandle.Invalidate(); \
    }

// Set a one-shot timer
#define SET_TIMER(Name, DelaySeconds, Lambda) \
    if (UWorld* World = GetWorld()) \
    { \
        FTimerDelegate Delegate = FTimerDelegate::CreateLambda(Lambda); \
        World->GetTimerManager().SetTimer(Name##TimerHandle, Delegate, DelaySeconds, false); \
    }

// Set a loop timer
#define SET_TIMER_LOOP(Name, DelaySeconds, Lambda) \
    if (UWorld* World = GetWorld()) \
    { \
        FTimerDelegate Delegate = FTimerDelegate::CreateLambda(Lambda); \
        World->GetTimerManager().SetTimer(Name##TimerHandle, Delegate, DelaySeconds, true); \
    }