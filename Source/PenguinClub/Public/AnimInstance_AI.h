// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimInstance_AI.generated.h"


class AS_AICharacter;
/**
 * 
 */
UCLASS()
class PENGUINCLUB_API UAnimInstance_AI : public UAnimInstance
{
	GENERATED_BODY()
	

		virtual void NativeInitializeAnimation() override;

	UFUNCTION(BlueprintCallable)
		void UpdateAnimationProperties(float DeltaTime);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
		AS_AICharacter* AI_Character;

public:

	UPROPERTY(BlueprintReadWrite)
		bool bIsAttack;

};
