// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance_PengFu.h"
#include "S_DynamicCollision_Component.h"
#include "S_SlopeComponent.h"
#include "PengFu_PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UAnimInstance_PengFu::NativeInitializeAnimation()
{
	PlayerCharacter = Cast<APengFu_PlayerCharacter>(TryGetPawnOwner());
}


void UAnimInstance_PengFu::UpdateAnimationProperties(float DeltaTime)
{
	if (PlayerCharacter == nullptr)
	{
		PlayerCharacter = Cast<APengFu_PlayerCharacter>(TryGetPawnOwner());
	}
	else {
		// Get the lateral speed of the character from velocity
		FVector Velocity{ PlayerCharacter->GetVelocity() };
		Velocity.Z = 0;
		Speed = Velocity.Size();

		JumpCount = PlayerCharacter->JumpCount;
		bIsAttacking = PlayerCharacter->bPrimaryAttack;
		bIsSlide = PlayerCharacter->bIsSliding;
		bWeaponEquipped = PlayerCharacter->bEquip;
		bBoostSlide = PlayerCharacter->bBoostLoad;
		bIsFall = PlayerCharacter->GetCharacterMovement()->IsFalling();
		LeanSlideValue = PlayerCharacter->LeanSlideDelta;
		bIsLoadingJump = PlayerCharacter->bLoadJump;
		bIsSwim = PlayerCharacter->bIsSwimming;
		bObjectInHand = PlayerCharacter->bIsBringingObject;
		bTaken = PlayerCharacter->bObjectTaken;

		PlayerLocation = PlayerCharacter->SlopeComp->CharacterLocation;
		PreviousPlayerLocation = PlayerCharacter->SlopeComp->PreviousCharacterLocation;

		if (!PlayerCharacter->GetCharacterMovement()->IsFalling()) 
		{
			PlayerCharacter->JumpCount = 0;
			JumpCount = PlayerCharacter->JumpCount;
		}

		if (PlayerCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0) {
			bIsAccelerating = true;
		}
		else {
			bIsAccelerating = false;
		}

		if (PlayerCharacter->bIsSprinting) {
			bIsSprint = true;
		}
		else {
			bIsSprint = false;
		}

		if (PlayerCharacter->JumpCount == 0) {
			PlayerCharacter->bJumpPressed = true;
			bJump = PlayerCharacter->bJumpPressed;
		}
		else { 
			PlayerCharacter->bJumpPressed = false;
		    bJump = PlayerCharacter->bJumpPressed;
		}
	}



}
