// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "S_AICharacter.generated.h"

class UBoxComponent;
class US_AttributeComponent;
class USoundCue;
UCLASS()
class PENGUINCLUB_API AS_AICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AS_AICharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadWrite)
	bool bIsAttacking;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "CollisionAttack",
		meta = (AllowPrivateAccess = "True"))
		UBoxComponent* CollisionMesh_R;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "CollisionAttack",
		meta = (AllowPrivateAccess = "True"))
		UBoxComponent* CollisionMesh_L;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		US_AttributeComponent* AttributeComp;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
		USoundCue* ImpactSound;

	UFUNCTION()
		void OnActorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
