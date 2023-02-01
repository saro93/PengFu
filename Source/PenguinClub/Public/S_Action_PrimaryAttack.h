// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "S_Action.h"
#include "S_Action_PrimaryAttack.generated.h"

/**
 * 
 */
UCLASS()
class PENGUINCLUB_API US_Action_PrimaryAttack : public US_Action
{
	GENERATED_BODY()
	
public:

	US_Action_PrimaryAttack();

	virtual void StartAction_Implementation(AActor* InstigatorActor) override;
	//virtual void StopAction_Implementation(AActor* InstigatorActor) override;
	UFUNCTION()
	void PrimaryAttack_TimerElapsed(AActor* InstigatorActor);

	UFUNCTION()
	void NextAttack_TimerElapsed(AActor* InstigatorActor);

	int32 ComboClubState;

	bool bNextAttack;

	FTimerHandle TimerHandle_AttackDelay;
	FTimerHandle TimerNextAttack;
	FTimerDelegate Delegate;
	FTimerDelegate DelegateNextAttack;
};
