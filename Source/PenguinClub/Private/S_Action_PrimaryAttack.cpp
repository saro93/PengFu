// Fill out your copyright notice in the Description page of Project Settings.


#include "S_Action_PrimaryAttack.h"
#include "PengFu_PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

US_Action_PrimaryAttack::US_Action_PrimaryAttack()
{
	ActionName = "PrimaryAttack";
	ComboClubState = 0;
	bNextAttack = false;


}

void US_Action_PrimaryAttack::StartAction_Implementation(AActor* InstigatorActor)
{
	Super::StartAction_Implementation(InstigatorActor);

	APengFu_PlayerCharacter* Character = Cast<APengFu_PlayerCharacter>(InstigatorActor);

	if (Character)
	{
		Delegate.BindUFunction(this, "PrimaryAttack_TimerElapsed", Character);
		DelegateNextAttack.BindUFunction(this, "NextAttack_TimerElapsed", Character);

		if (!Character->bPrimaryAttack || bNextAttack) {

			Character->bPrimaryAttack = true;
			if (Character->AttackClub_Montage && Character->bEquip)
			{
				ComboClubState += 1;
				UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();

				switch (ComboClubState) 
				{
				case 1:
					bNextAttack = false;
					Character->bPrimaryAttack = false;
					GetWorld()->GetTimerManager().SetTimer(TimerHandle_AttackDelay, Delegate, 0.3, false);
					GetWorld()->GetTimerManager().SetTimer(TimerNextAttack, DelegateNextAttack, 0.15, false);
					if (AnimInstance)
					{
						AnimInstance->Montage_Play(Character->AttackClub_Montage);
						AnimInstance->Montage_JumpToSection(FName("ClubCombo1"));
					}


					break;
				case 2:
					if (bNextAttack) {
						bNextAttack = false;
						Character->bPrimaryAttack = false;
						GetWorld()->GetTimerManager().ClearTimer(TimerHandle_AttackDelay);
						GetWorld()->GetTimerManager().ClearTimer(TimerNextAttack);
						GetWorld()->GetTimerManager().SetTimer(TimerHandle_AttackDelay, Delegate, 0.2, false);
						GetWorld()->GetTimerManager().SetTimer(TimerNextAttack, DelegateNextAttack, 0.10, false);
						if (AnimInstance)
						{
							AnimInstance->Montage_Play(Character->AttackClub_Montage);
							AnimInstance->Montage_JumpToSection(FName("ClubCombo2"));
						}					
					}
					break;

				case 3:

					if (bNextAttack) {
						bNextAttack = false;
						Character->bPrimaryAttack = false;
						GetWorld()->GetTimerManager().ClearTimer(TimerHandle_AttackDelay);
						GetWorld()->GetTimerManager().ClearTimer(TimerNextAttack);
						GetWorld()->GetTimerManager().SetTimer(TimerHandle_AttackDelay, Delegate, 0.6, false);
						if (AnimInstance)
						{
							AnimInstance->Montage_Play(Character->AttackClub_Montage);
							AnimInstance->Montage_JumpToSection(FName("ClubCombo3"));
						}
					}
					break;

					break;
				default:
					break;
				}
			}
			else {
				GetWorld()->GetTimerManager().SetTimer(TimerHandle_AttackDelay, Delegate, 0.5 ,false);
				UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
				if (AnimInstance)
				{
					AnimInstance->Montage_Play(Character->AttackPunch_Montage);
					AnimInstance->Montage_JumpToSection(FName("Default"));
					//Character->GetCharacterMovement()->MaxWalkSpeed = 100;
				}
			}
		}
	}

	
}

void US_Action_PrimaryAttack::PrimaryAttack_TimerElapsed(AActor* InstigatorActor)
{
	APengFu_PlayerCharacter* Character = Cast<APengFu_PlayerCharacter>(InstigatorActor);

	if (Character && !Character->bEquip)
	{
		UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
		if (AnimInstance) {
			AnimInstance->Montage_Stop(0.2, Character->AttackPunch_Montage);
			Character->bPrimaryAttack = false;
		}
		//Character->GetCharacterMovement()->MaxWalkSpeed = 600;
	}
	else {
		UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
		if (AnimInstance) {
			AnimInstance->Montage_Stop(0.2, Character->AttackClub_Montage);
			Character->bPrimaryAttack = false;
			
		}
		//Character->GetCharacterMovement()->MaxWalkSpeed = 600;
		//bNextAttack = false;
		ComboClubState = 0;
	}

	StopAction(InstigatorActor);
	
}

void US_Action_PrimaryAttack::NextAttack_TimerElapsed(AActor* InstigatorActor)
{
		bNextAttack = true;
}

