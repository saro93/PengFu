// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "S_SlopeComponent.generated.h"

class APengFu_PlayerCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PENGUINCLUB_API US_SlopeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	US_SlopeComponent();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Settings")
		FVector DefaultMeshLocation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Settings")
		FVector SlidingMeshLocation = FVector(-40, 0, -100);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Settings")
		float FloorAngle;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character Settings")
		FVector PreviousCharacterLocation = FVector(0, 0, 1);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character Settings")
		FVector CharacterLocation = FVector(0, 0, 1);

	FRotator NewRotation = FRotator(0, -90, 0);

	APengFu_PlayerCharacter* Character;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
