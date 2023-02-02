// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimInstance_PengFu.generated.h"

/**
 * 
 */
UCLASS()
class PENGUINCLUB_API UAnimInstance_PengFu : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	virtual void NativeInitializeAnimation() override;

	UFUNCTION(BlueprintCallable)
		void UpdateAnimationProperties(float DeltaTime);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		class APengFu_PlayerCharacter* PlayerCharacter;

	/** Actual speed of the character*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement",
		meta = (AllowPrivateAccess = "true"))
		float Speed;

	/** Whether or not character is moving*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement",
		meta = (AllowPrivateAccess = "true"))
		bool bIsAccelerating;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement",
		meta = (AllowPrivateAccess = "true"))
		bool bIsSprint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement",
		meta = (AllowPrivateAccess = "true"))
		bool bIsSlide;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement",
		meta = (AllowPrivateAccess = "true"))
		bool bJump;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement",
		meta = (AllowPrivateAccess = "true"))
		bool bIsAttacking;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement",
		meta = (AllowPrivateAccess = "true"))
		bool bIsFall;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement",
		meta = (AllowPrivateAccess = "true"))
		float LeanSlideValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		bool bBoostSlide;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		bool bIsLoadingJump;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement",
		meta = (AllowPrivateAccess = "true"))
		bool bWeaponEquipped;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement",
		meta = (AllowPrivateAccess = "true"))
		int JumpCount;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
		float SlideTraceUp;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
		float SlideTraceLow;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character Settings")
		FVector PreviousPlayerLocation;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character Settings")
		FVector PlayerLocation;

};
