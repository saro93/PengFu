// Fill out your copyright notice in the Description page of Project Settings.


#include "S_Action.h"
//#include "DrawDebugHelpers.h"

void US_Action::StartAction_Implementation(AActor* InstigatorActor)
{
	//UE_LOG(LogTemp, Log, TEXT("Running: %s"), *GetNameSafe(this));
}

void US_Action::StopAction_Implementation(AActor* InstigatorActor)
{
	//UE_LOG(LogTemp, Log, TEXT("Stopped: %s"), * GetNameSafe(this));
}

UWorld* US_Action::GetWorld() const
{
	UActorComponent* Comp = Cast<UActorComponent> (GetOuter());
	if (Comp) {
		return Comp->GetWorld();
	}

	return nullptr;
}
