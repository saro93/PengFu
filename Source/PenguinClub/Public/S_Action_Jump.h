// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "S_Action.h"
#include "S_Action_Jump.generated.h"

/**
 * 
 */
UCLASS()
class PENGUINCLUB_API US_Action_Jump : public US_Action
{
	GENERATED_BODY()
	
public:

	US_Action_Jump();

	virtual void StartAction_Implementation(AActor* InstigatorActor) override;
	virtual void StopAction_Implementation(AActor* InstigatorActor) override;

	FTimerHandle TimerTrigger_Jump;
	FTimerDelegate DelegateJump;

	UFUNCTION()
		void Jump_TimerElapsed(AActor* InstigatorActor);

};
