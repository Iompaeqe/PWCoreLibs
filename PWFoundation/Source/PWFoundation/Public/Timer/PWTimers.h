// Copyright (c) 2025 Metehan Goksel Kurtulan (Iompaeqe)

#pragma once

#include "CoreMinimal.h"
#include "TimerManager.h"
#include <functional>

class PWFOUNDATION_API FPWTimers
{
public:
    struct TimerHandle
    {
        FTimerHandle UEHandle;
        std::function<void()> Callback;
    };

    FPWTimers();
    ~FPWTimers();
    
    static void WaitAfterFrame(std::function<void()> Callback);
    static void WaitUntil(std::function<bool()> Condition, std::function<void()> Callback);
    static void WaitForSeconds(float Seconds, std::function<void()> Callback);
    static void Delay(const FString& UniqueName, const float Time, std::function<void()> Callback);
    static void DelayRepeat(const FString& UniqueName, const float Time, std::function<bool()> Callback);
    static void Cancel(const FString& UniqueName, bool bLog = true);
    /**
     * Removes every timer, intended to be used when the game is closing.
     * Use with caution.
     */
    static void CancelEverything();

private:
    static TMap<FString, TimerHandle> Timers;
    static FCriticalSection TimerCriticalSection;
};