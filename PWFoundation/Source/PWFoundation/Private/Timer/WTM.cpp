// Copyright (c) 2025 Metehan Goksel Kurtulan (Iompaeqe)

#include "Timer/WTM.h"


TMap<FString, WTM::TimerHandle> WTM::Timers = TMap<FString, WTM::TimerHandle>();
FCriticalSection WTM::TimerCriticalSection;

WTM::WTM()
{
}

WTM::~WTM()
{
	CancelEverything();
}

void WTM::WaitAfterFrame(std::function<void()> Callback)
{
	if (!GWorld)
	{
		return;
	}

	AsyncTask(ENamedThreads::GameThread, [Callback]()
	{
		Callback();
	});
}

void WTM::WaitUntil(std::function<bool()> Condition, std::function<void()> Callback)
{
	if (!GWorld)
	{
		return;
	}

	AsyncTask(ENamedThreads::GameThread, [Condition, Callback]()
	{
		if (Condition())
		{
			Callback();
		}
		else
		{
			WTM::WaitUntil(Condition, Callback);
		}
	});

}

void WTM::WaitForSeconds(float Seconds, std::function<void()> Callback)
{
	if (!GWorld || Seconds <= 0.0f)
	{
		return;
	}

	FTimerDelegate TimerDel;
	TimerDel.BindLambda([Callback]() { Callback(); });

	FTimerHandle TimerHandle;
	GWorld->GetTimerManager().SetTimer(TimerHandle, TimerDel, Seconds, false);
}

void WTM::Delay(const FString& UniqueName, const float Time, std::function<void()> Callback)
{
	//logfuncmsgf("UniqueName: %s", *UniqueName);
	if (!GWorld)
	{
		return;
	}

	Cancel(UniqueName, false);

	TimerHandle NewHandle;
	NewHandle.Callback = Callback;

	FTimerDelegate TimerDel;
	TimerDel.BindLambda([UniqueName, Callback]()
	{
		Callback();
		if (GWorld)
			AsyncTask(ENamedThreads::GameThread, [UniqueName]()
			{
				WTM::Cancel(UniqueName); // Always cancel from the main thread
			});
	});

	GWorld->GetTimerManager().SetTimer(NewHandle.UEHandle, TimerDel, Time, false);

	{
		FScopeLock Lock(&TimerCriticalSection);
		Timers.Add(UniqueName, NewHandle);
	}
}

void WTM::DelayRepeat(const FString& UniqueName, const float Time, std::function<bool()> Callback)
{
	//logfuncmsgf("UniqueName: %s", *UniqueName);
	if (!GWorld)
	{
		return;
	}

	Cancel(UniqueName, false);

	FScopeLock Lock(&TimerCriticalSection);
	TimerHandle NewHandle;
	NewHandle.Callback = [UniqueName, Time, Callback]()
	{
		FScopeLock Lock(&TimerCriticalSection);
		if (Callback())
		{
			if (GWorld)
				AsyncTask(ENamedThreads::GameThread, [UniqueName]()
				{
					WTM::Cancel(UniqueName); // Always cancel from the main thread
				});
		}
		else if (GWorld && WTM::Timers.Contains(UniqueName))
		{
			GWorld->GetTimerManager().SetTimer(Timers[UniqueName].UEHandle, Timers[UniqueName].Callback, Time, false);
		}
	};

	GWorld->GetTimerManager().SetTimer(NewHandle.UEHandle, NewHandle.Callback, Time, false);
	{
		Timers.Add(UniqueName, NewHandle);
	}
}

void WTM::Cancel(const FString& UniqueName, bool bLog)
{
	//logfuncmsgf("UniqueName: %s", *UniqueName);
	if (!GWorld)
		return;
	
	FScopeLock Lock(&TimerCriticalSection);
	if (TimerHandle* HandlePtr = Timers.Find(UniqueName))
	{
		FTimerHandle& Handle = HandlePtr->UEHandle;
		if (Handle.IsValid() && GWorld->GetTimerManager().IsTimerActive(Handle))
		{
			GWorld->GetTimerManager().ClearTimer(Handle);
		}
		Timers.Remove(UniqueName);
		if (bLog)
			UE_LOG(LogTemp, Log, TEXT("Timer canceled: %s"), *UniqueName);
	}
	else
	{
		if (bLog)
			UE_LOG(LogTemp, Warning, TEXT("Timer not found for cancel: %s"), *UniqueName);
	}
}

void WTM::CancelEverything()
{
	//logfunc();
	if (!GWorld)
	{
		UE_LOG(LogTemp, Warning, TEXT("GWorld is null. Cannot cancel all timers."));
		return;
	}

	FScopeLock Lock(&TimerCriticalSection);
	for (TTuple<FString, TimerHandle>& Timer : Timers)
	{
		FTimerHandle& Handle = Timer.Value.UEHandle;
		if (Handle.IsValid() && GWorld->GetTimerManager().IsTimerActive(Handle))
			GWorld->GetTimerManager().ClearTimer(Handle);
	}
	Timers.Empty();
	UE_LOG(LogTemp, Log, TEXT("All timers have been canceled."));
}
