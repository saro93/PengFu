// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "S_Tool.generated.h"

class UStaticMeshComponent;
class APengFu_PlayerCharacter;

UCLASS()
class PENGUINCLUB_API AS_Tool : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AS_Tool();

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Item Proprietes", meta = (AllowPrivateAccess = "True"))
		FString Tool_Name;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Item Proprietes", meta = (AllowPrivateAccess = "True"))
		USkeletalMeshComponent* Tool_Sk_Mesh;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Item Proprietes", meta = (AllowPrivateAccess = "True"))
		class UBoxComponent* CollisionBox;



public:

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Item Proprietes",
		meta = (AllowPrivateAccess = "True"))
		class USphereComponent* CollisionSphere;

	/** pop up widget , when the plaier look at the item*/
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Item Proprietes",
		meta = (AllowPrivateAccess = "True"))
		class UWidgetComponent* PickupWidget;

	FRotator WidgetRotation;

	UPROPERTY()
		AActor* OverlappedActor;

	FORCEINLINE UWidgetComponent* GetWidget() const { return PickupWidget; }

	void DeactivateComponents();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	//virtual void PostInitializeComponents() override;

	FORCEINLINE UBoxComponent* GetCollisionBox() { return CollisionBox; }

	UFUNCTION()
		void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnActorEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UFUNCTION()
	void OnEnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
