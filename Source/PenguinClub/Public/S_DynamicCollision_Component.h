// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/TimelineComponent.h"
#include "S_DynamicCollision_Component.generated.h"

class APengFu_PlayerCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PENGUINCLUB_API US_DynamicCollision_Component : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	US_DynamicCollision_Component();

	FTimeline SlidingTime;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Settings")
		float DefaultCapsuleHalfHeight;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Settings")
		float DefaultCapsuleRadius;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Settings")
		FVector DefaultMeshLocation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Settings")
		FVector SlidingMeshLocation = FVector(-40, 0, -100);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Settings")
		float SlidingCapsuleHalfHeight = 40.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Settings")
		float SlidingCapsuleRadius = 40;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Settings")
		float FloorAngleUp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Settings")
		float FloorAngle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Settings")
		float FloorAngleLow;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Settings")
		UCurveFloat* SlidingCurve = nullptr;

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



private:
	UFUNCTION()
		void ActionUpdate(float Alpha);

	UFUNCTION()
		void ActionFinish();
		
};
