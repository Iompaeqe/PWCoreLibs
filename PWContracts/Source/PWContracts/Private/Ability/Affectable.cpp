// Copyright (c) 2025 Metehan Goksel Kurtulan (Iompaeqe)


#include "Ability/Affectable.h"

#include "Ability/EffectReceiver.h"
#include "GameFramework/Actor.h"

UObject* IAffectable::Find(AActor* Actor)
{
	if (!Actor) return nullptr;

	UObject* Receiver = Actor->Implements<UEffectReceiver>() ? IEffectReceiver::Execute_GetEffectReceiver(Actor) : Actor;
	return Receiver && Receiver->Implements<UAffectable>() ? Receiver : nullptr;
}
