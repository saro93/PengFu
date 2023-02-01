// Fill out your copyright notice in the Description page of Project Settings.


#include "S_Action_Sprint.h"
#include "PengFu_PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

US_Action_Sprint::US_Action_Sprint()
{
	ActionName = "Sprint";
	Max_SprinSpeed = 1000;
}

void US_Action_Sprint::StartAction_Implementation(AActor* InstigatorActor)
{
	Super::StartAction_Implementation(InstigatorActor);

	APengFu_PlayerCharacter* Character = Cast<APengFu_PlayerCharacter>(InstigatorActor);

	if (Character) 
	{
		Character->GetCharacterMovement()->MaxWalkSpeed = Max_SprinSpeed;
		Character->bIsSprinting = true;
	}

}

void US_Action_Sprint::StopAction_Implementation(AActor* InstigatorActor)
{
	Super::StopAction_Implementation(InstigatorActor);

	APengFu_PlayerCharacter* Character = Cast<APengFu_PlayerCharacter>(InstigatorActor);

	if (Character)
	{
		Character->GetCharacterMovement()->MaxWalkSpeed = 600;
		Character->bIsSprinting = false;
	}
}
