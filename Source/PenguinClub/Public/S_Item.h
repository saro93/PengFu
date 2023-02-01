// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "S_InteractableComponent.h"
#include "SGamePlayInterface.h"
#include "S_Item.generated.h"

UCLASS()
class PENGUINCLUB_API AS_Item : public AActor , public ISGamePlayInterface
{
	GENERATED_BODY()

		

public:	
	AS_Item();

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Item Proprietes",meta = (AllowPrivateAccess = "True"))
		USkeletalMeshComponent* ItemMesh;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Item Proprietes", meta = (AllowPrivateAccess = "True"))
		int32 ItemCount;

	void Interact_Implementation(APawn* InstigatorPawn);

protected:

	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

public:	

	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Item Proprietes",meta = (AllowPrivateAccess = "True"))
		FString ItemName;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Item Proprietes",meta = (AllowPrivateAccess = "True"))
		class UBoxComponent* CollisionBox;

public:

	FORCEINLINE USkeletalMeshComponent* GetItemMesh() { return ItemMesh; }
	FORCEINLINE UBoxComponent* GetCollisionBox() { return CollisionBox; }

};
