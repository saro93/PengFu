// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "S_Collectibles.generated.h"

class USoundCue;

UCLASS()
class PENGUINCLUB_API AS_Collectibles : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AS_Collectibles();

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Item Proprietes", meta = (AllowPrivateAccess = "True"))
		FString CoinName;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Item Proprietes", meta = (AllowPrivateAccess = "True"))
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
		int Amount;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
		USoundCue* ImpactSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnActorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnActorEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
