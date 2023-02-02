// Fill out your copyright notice in the Description page of Project Settings.


#include "S_Action_Jump.h"
#include "PengFu_PlayerCharacter.h"
#include "S_DynamicCollision_Component.h"
#include "GameFramework/CharacterMovementComponent.h"

US_Action_Jump::US_Action_Jump() 
{
	ActionName = "Jump";

}

void US_Action_Jump::StartAction_Implementation(AActor* InstigatorActor)
{
	Super::StartAction_Implementation(InstigatorActor);


	if (APengFu_PlayerCharacter* Character = Cast<APengFu_PlayerCharacter>(InstigatorActor)) 
	{
		if (Character->bJumpPressed && !Character->GetCharacterMovement()->IsFalling())
		{
			if (Character->JumpCount == 0) {

				if (!Character->bIsSliding)
				{
					DelegateJump.BindUFunction(this, "Jump_TimerElapsed", Character);
					GetWorld()->GetTimerManager().ClearTimer(TimerTrigger_Jump);
					GetWorld()->GetTimerManager().SetTimer(TimerTrigger_Jump, DelegateJump, 0.3, false);
					return;
				}
				else if (Character->bIsSliding)
				{
					Character->bBoostLoad = true;
					return;
				}
			}
		}
	}
}

void US_Action_Jump::StopAction_Implementation(AActor* InstigatorActor)
{
	Super::StopAction_Implementation(InstigatorActor);
	
	if (APengFu_PlayerCharacter* Character = Cast<APengFu_PlayerCharacter>(InstigatorActor)) {
		
		if (!Character->bJumpPressed && !Character->GetCharacterMovement()->IsFalling())
		{
			if (Character->JumpCount > 1) { GetWorld()->GetTimerManager().ClearTimer(TimerTrigger_Jump); return; }

			if (!Character->bIsSliding && !Character->GetCharacterMovement()->IsFalling() && Character->JumpCount == 0)
			{
				Character->JumpCount += 1;
				GetWorld()->GetTimerManager().ClearTimer(TimerTrigger_Jump);
				Character->LaunchCharacter(FVector(0, 0, 750), false, false);
				Character->CollisionComp->JumpingTime.Play();

			}
			else if (Character->bBoostLoad)
			{
				FVector ForwardVector = Character->GetActorForwardVector();
				FVector LaunchVector = ForwardVector * 500.0f;

				Character->LaunchCharacter(LaunchVector, false, false);
				Character->bBoostLoad = false;
				return;
			}
			//GetWorld()->GetTimerManager().ClearTimer(TimerTrigger_Jump);
		}
	}

}

void US_Action_Jump::Jump_TimerElapsed(AActor* InstigatorActor)
{
	APengFu_PlayerCharacter* Character = Cast<APengFu_PlayerCharacter>(InstigatorActor);
	
		if (Character->JumpCount > 1) { GetWorld()->GetTimerManager().ClearTimer(TimerTrigger_Jump); return; }

		Character->JumpCount += 1;
		Character->LaunchCharacter(FVector(0, 0, 1000), false, false);
		Character->CollisionComp->JumpingTime.Play();
}
