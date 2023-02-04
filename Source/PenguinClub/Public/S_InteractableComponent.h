// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "S_InteractableComponent.generated.h"

class US_WorldUserWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PENGUINCLUB_API US_InteractableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	US_InteractableComponent();

	void PrimaryInteract();

	APawn* MyPawn;

	UPROPERTY()
		US_WorldUserWidget* DefaultWidgetInstance;

protected:

	void FindBestInteractable();

	virtual void BeginPlay() override;

	UPROPERTY()
	AActor* FocusedActor;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	float TraceDistance;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	float TraceRadius;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	TEnumAsByte<ECollisionChannel> CollisionChannel;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
		TSubclassOf<US_WorldUserWidget> DefaultWidgetClass;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
