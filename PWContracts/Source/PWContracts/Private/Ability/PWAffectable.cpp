// Copyright (c) 2025 Metehan Goksel Kurtulan (Iompaeqe)


#include "Ability/PWAffectable.h"

#include "Ability/PWEffectReceiver.h"
#include "GameFramework/Actor.h"

UObject* IPWAffectable::Find(AActor* Actor)
{
	if (!Actor) return nullptr;

	UObject* Receiver = Actor->Implements<UPWEffectReceiver>() ? IPWEffectReceiver::Execute_GetEffectReceiver(Actor) : Actor;
	return Receiver && Receiver->Implements<UPWAffectable>() ? Receiver : nullptr;
}
