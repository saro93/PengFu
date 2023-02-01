// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "S_ActionComponent.generated.h"

class US_Action;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PENGUINCLUB_API US_ActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	US_ActionComponent();

	UFUNCTION(BlueprintCallable, Category = "Actions")
		void AddAction(TSubclassOf<US_Action> ActionClass);

	UFUNCTION(BlueprintCallable, Category = "Actions")
		bool StartActionByName(AActor* InstigatorActor, FName ActionName);

	UFUNCTION(BlueprintCallable, Category = "Actions")
		bool StopActionByName(AActor* InstigatorActor, FName ActionName);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<US_Action*> Actions;

	UPROPERTY(EditAnywhere, Category = "Action")
		TArray<TSubclassOf <US_Action>> DefaultActions;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
