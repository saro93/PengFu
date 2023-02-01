// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "S_Action.h"
#include "S_Action_Slide.generated.h"

/**
 * 
 */
UCLASS()
class PENGUINCLUB_API US_Action_Slide : public US_Action
{
	GENERATED_BODY()

	US_Action_Slide();

	virtual void StartAction_Implementation(AActor* InstigatorActor) override;
	virtual void StopAction_Implementation(AActor* InstigatorActor) override;

};
