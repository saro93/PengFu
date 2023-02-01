// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "S_Action.h"
#include "S_Action_Sprint.generated.h"

/**
 * 
 */
UCLASS()
class PENGUINCLUB_API US_Action_Sprint : public US_Action
{
	GENERATED_BODY()

public:

	US_Action_Sprint();

    UPROPERTY(EditDefaultsOnly)
		float Max_SprinSpeed;


	virtual void StartAction_Implementation(AActor* InstigatorActor) override;
	virtual void StopAction_Implementation(AActor* InstigatorActor) override;

};
