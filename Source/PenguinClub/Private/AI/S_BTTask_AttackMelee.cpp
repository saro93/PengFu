// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/S_BTTask_AttackMelee.h"
#include "AIController.h"
#include "AI/S_AICharacter.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type US_BTTask_AttackMelee::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) 
{
	AAIController* MyController = OwnerComp.GetAIOwner();
	if (ensure(MyController))
	{
		AS_AICharacter* MyPawn = Cast<AS_AICharacter>(MyController->GetPawn());
		if (MyPawn == nullptr) 
		{
			return EBTNodeResult::Failed;
		}

		AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
		if (TargetActor == nullptr) 
		{
			return EBTNodeResult::Failed;
		}

		MyPawn->bIsAttacking = true;
	}

	return EBTNodeResult::Failed;
}
