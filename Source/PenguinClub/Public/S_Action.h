// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "S_Action.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PENGUINCLUB_API US_Action : public UObject
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly)
		FName ActionName;

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
		void StartAction(AActor* InstigatorActor);

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
		void StopAction(AActor* InstigatorActor);

	UWorld* GetWorld() const override;
};
