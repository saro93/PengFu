// Fill out your copyright notice in the Description page of Project Settings.


#include "S_ActionComponent.h"
#include "S_Action.h"

US_ActionComponent::US_ActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void US_ActionComponent::BeginPlay()
{
	Super::BeginPlay();

	for (TSubclassOf<US_Action> ActionClass : DefaultActions)
	{
		AddAction(ActionClass);
	}

}


// Called every frame
void US_ActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void US_ActionComponent::AddAction(TSubclassOf<US_Action> ActionClass)
{
	if (!ensure(ActionClass)) 
	{
		return;
	}

	US_Action* NewAction = NewObject<US_Action>(this, ActionClass);
	if (NewAction) {
		Actions.Add(NewAction);
	}
}

bool US_ActionComponent::StartActionByName(AActor* InstigatorActor, FName ActionName)
{
	for (US_Action* Action : Actions) {
		if (Action && Action->ActionName == ActionName) {
			Action->StartAction(InstigatorActor);
			return true;
		}
	}

	return false;
}

bool US_ActionComponent::StopActionByName(AActor* InstigatorActor, FName ActionName)
{
	for (US_Action* Action : Actions) {
		if (Action && Action->ActionName == ActionName) {
			Action->StopAction(InstigatorActor);
			return true;
		}
	}

	return false;
}