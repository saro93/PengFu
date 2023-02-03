// Fill out your copyright notice in the Description page of Project Settings.


#include "S_Action_Slide.h"
#include "PengFu_PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "S_DynamicCollision_Component.h"

US_Action_Slide::US_Action_Slide() 
{
	ActionName = "Slide";
}

void US_Action_Slide::StartAction_Implementation(AActor* InstigatorActor)
{
	Super::StartAction_Implementation(InstigatorActor);
	APengFu_PlayerCharacter* Character = Cast<APengFu_PlayerCharacter>(InstigatorActor);

	if (Character)
	{
		if (!Character->GetCharacterMovement()->IsFalling() && !Character->bIsSwimming) {
			Character->CollisionComp->SlidingTime.Play();
			Character->bIsSliding = true;
			//Character->GetCharacterMovement()->GroundFriction = 0.f;
			//Character->GetCharacterMovement()->BrakingDecelerationWalking = 100;
			//Character->GetCharacterMovement()->MaxWalkSpeed = Character->speedLying;
		}
	}
	
}


void US_Action_Slide::StopAction_Implementation(AActor* InstigatorActor)
{
	Super::StopAction_Implementation(InstigatorActor);

	APengFu_PlayerCharacter* Character = Cast<APengFu_PlayerCharacter>(InstigatorActor);

	if (Character)
	{
		if (!Character->bIsSwimming) 
		{
			Character->CollisionComp->SlidingTime.Reverse();
			Character->bIsSliding = false;
			//Character->GetCharacterMovement()->GroundFriction = 8.f;
			//Character->GetCharacterMovement()->BrakingDecelerationWalking = 2048.f;
			//Character->GetCharacterMovement()->MaxWalkSpeed = 600;
		}
	}

	
}