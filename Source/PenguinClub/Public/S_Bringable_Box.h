// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "S_Item.h"
#include "S_Bringable_Box.generated.h"

/**
 * 
 */
UCLASS()
class PENGUINCLUB_API AS_Bringable_Box : public AS_Item
{
	GENERATED_BODY()
	
public:
	FTimerHandle Timer_ObjectAttack;
	FTimerDelegate Delegate;
	void Interact_Implementation(APawn* InstigatorPawn);

	UFUNCTION()
		void TimerAttachment(AActor* InstigatorActor);
};
