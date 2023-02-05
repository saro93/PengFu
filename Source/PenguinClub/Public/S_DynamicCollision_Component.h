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

	FTimeline JumpingTime;

	FTimeline SwimmingTime;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Settings")
		float DefaultCapsuleHalfHeight;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Settings")
		float DefaultCapsuleRadius;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Settings")
		FVector DefaultMeshLocation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Settings")
		FVector SlidingMeshLocation = FVector(-40, 0, -100);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Settings")
		FVector JumpingMeshLocation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Settings")
		FVector SwimmingMeshLocation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Settings")
		float SlidingCapsuleHalfHeight = 40.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Settings")
		float JumpingCapsuleHalfHeight = 56.25f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Settings")
		float SwimmingCapsuleHalfHeight = 10.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Settings")
		float SlidingCapsuleRadius = 40;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Settings")
		float JumpingCapsuleRadius = 20.5f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Settings")
		float SwimmingCapsuleRadius = 10;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Settings")
		UCurveFloat* SlidingCurve = nullptr;

	APengFu_PlayerCharacter* Character;



protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;



private:
	UFUNCTION()
		void SlideUpdate(float Alpha);

	UFUNCTION()
		void JumpUpdate(float Alpha);

	UFUNCTION()
		void SwimUpdate(float Alpha);

	UFUNCTION()
		void ActionFinish();
		
};
