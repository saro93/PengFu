// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance_AI.h"
#include "AI/S_AICharacter.h"

void UAnimInstance_AI::NativeInitializeAnimation()
{
	AI_Character = Cast<AS_AICharacter>(TryGetPawnOwner());
}

void UAnimInstance_AI::UpdateAnimationProperties(float DeltaTime)
{
	if (AI_Character == nullptr)
	{
		AI_Character = Cast<AS_AICharacter>(TryGetPawnOwner());
	}
	else 
	{
		bIsAttack = AI_Character->bIsAttacking;
	}
}
