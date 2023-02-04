// Fill out your copyright notice in the Description page of Project Settings.


#include "S_Bringable_Box.h"
#include "PengFu_PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/UserWidget.h"
#include "S_InteractableComponent.h"
#include "S_WorldUserWidget.h"

void AS_Bringable_Box::Interact_Implementation(APawn* InstigatorPawn)
{
	if (APengFu_PlayerCharacter* Char = Cast<APengFu_PlayerCharacter>(InstigatorPawn)) 
	{
		Char->GetMesh()->GetAnimInstance()->Montage_Play(Char->BringObject_Montage, 0.75);
		//Char->PlayAnimMontage(Char->BringObject_Montage,1,FName("StartBring"));
		Char->bIsBringingObject = true;
		Char->GetCharacterMovement()->DisableMovement();
		Delegate.BindUFunction(this, "TimerAttachment", Char);
		GetWorld()->GetTimerManager().SetTimer(Timer_ObjectAttack, Delegate, 0.4, false);
		Char->InteractionComp->DefaultWidgetInstance->RemoveFromParent();

	}
}

void AS_Bringable_Box::TimerAttachment(AActor* InstigatorActor)
{
	if (APengFu_PlayerCharacter* Char = Cast<APengFu_PlayerCharacter>(InstigatorActor))
	{
		Char->bObjectTaken = true;
		Char->bIsBringingObject = false;
		Char->BoxTaken = this;
		
		this->AttachToComponent(Char->GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("ObjectTaken_Socket"));
		Char->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	}
}
