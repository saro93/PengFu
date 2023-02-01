// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/S_AICharacter.h"
#include "Components/BoxComponent.h"
#include "PengFu_PlayerCharacter.h"
#include "S_AttributeComponent.h"

// Sets default values
AS_AICharacter::AS_AICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionMesh_L = CreateDefaultSubobject<UBoxComponent>(TEXT("Hand_L_Collision"));
	CollisionMesh_R = CreateDefaultSubobject<UBoxComponent>(TEXT("Hand_R_Collision"));

	CollisionMesh_R->SetupAttachment(GetMesh());
	CollisionMesh_L->SetupAttachment(GetMesh());

	CollisionMesh_L->SetBoxExtent(FVector(7,7,7));
	CollisionMesh_R->SetBoxExtent(FVector(7,7,7));

	CollisionMesh_L->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("Arm_Low_LSocket"));
	CollisionMesh_R->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("Arm_Low_RSocket"));

	CollisionMesh_L->OnComponentBeginOverlap.AddDynamic(this, &AS_AICharacter::OnActorBeginOverlap);
	CollisionMesh_R->OnComponentBeginOverlap.AddDynamic(this, &AS_AICharacter::OnActorBeginOverlap);
	bIsAttacking = false;
}

// Called when the game starts or when spawned
void AS_AICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AS_AICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AS_AICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AS_AICharacter::OnActorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bIsAttacking)
	{
		if (APengFu_PlayerCharacter* Char = Cast<APengFu_PlayerCharacter>(OtherActor)) 
		{
			Char->AttributeComp->ApplyHealthChange(-10);
		}
	}
}

