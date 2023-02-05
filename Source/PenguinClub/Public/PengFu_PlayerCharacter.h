// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TimelineComponent.h"
#include "PengFu_PlayerCharacter.generated.h"

class AS_Tool;
class UCurveFloat;
class US_InteractableComponent;
class US_SlopeComponent;
class US_AttributeComponent;
class US_ActionComponent;
class US_DynamicCollision_Component;
class UBoxComponent;
class AS_Bringable_Box;

UCLASS()
class PENGUINCLUB_API APengFu_PlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	APengFu_PlayerCharacter();


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Item",
		meta = (AllowPrivateAccess = "True"))
		class USphereComponent* CollectionSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		US_InteractableComponent* InteractionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		US_AttributeComponent* AttributeComp;

	FORCEINLINE US_AttributeComponent* GetAttibuteComp() const { return AttributeComp; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		US_ActionComponent* ActionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		US_DynamicCollision_Component* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		US_SlopeComponent* SlopeComp;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "CollisionSwim",
		meta = (AllowPrivateAccess = "True"))
		UBoxComponent* CollisionMesh;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Settings")
	   float speedLying;

	UPROPERTY(BlueprintReadOnly, Category = "Attack")
		bool bPrimaryAttack;

	UPROPERTY(BlueprintReadOnly, Category = "Attack")
		bool bEquip;

	UPROPERTY(BlueprintReadOnly, Category = "Attack")
		bool bClubInInvenctory;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
		bool bIsSprinting;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	    bool bIsSliding;
	
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
		bool bObjectTaken;

	UPROPERTY(BlueprintReadWrite, Category = "Movement")
		bool bIsBringingObject;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement",
		meta = (AllowPrivateAccess = "true"))
		bool bJumpPressed;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
		bool bBoostLoad;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
		bool bLoadJump;

	UPROPERTY(BlueprintReadWrite, Category = "Movement")
		bool bIsSwimming;

	UPROPERTY(BlueprintReadWrite, Category = "Movement")
		int JumpCount;

	UPROPERTY(BlueprintReadWrite, Category = "Movement")
        float LeanSlideDelta;

        AS_Tool* EquippedWeapon;

	UPROPERTY(BlueprintReadWrite, Category = "Movement")
		AS_Bringable_Box* BoxTaken;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
		TSubclassOf<AS_Tool> StandardWeapon;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat",
		meta = (AllowPrivateAccess = "true"))
		UAnimMontage* AttackClub_Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat",meta = (AllowPrivateAccess = "true"))
		UAnimMontage* AttackPunch_Montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AmbientalAction", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* BringObject_Montage;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void PrimaryInteract();

	void PickUpObjects();

	void SprintStart();
	void SprintStop();

	void Slide();
	void Slide_Stop();

	void PrimaryAttack();

	void EquipAction();

	void Jump();
	void JumpStop();

	void LeaveBox();

	AS_Tool* SpawnDefaultWeapon();

public:	

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



};
