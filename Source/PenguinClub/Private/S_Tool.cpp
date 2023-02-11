// Fill out your copyright notice in the Description page of Project Settings.


#include "S_Tool.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "AI/S_AICharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/WidgetComponent.h"
#include "S_AttributeComponent.h"
#include "PengFu_PlayerCharacter.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AS_Tool::AS_Tool()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Tool_Sk_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal_Mesh"));
	SetRootComponent(Tool_Sk_Mesh);

	Tool_Name = FString("Default");

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);

	PickupWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PickupWidget"));
	PickupWidget->SetupAttachment(RootComponent);

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereOverlap"));
	CollisionSphere->SetupAttachment(CollisionBox);

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AS_Tool::OnActorOverlap);
	CollisionSphere->OnComponentEndOverlap.AddDynamic(this, &AS_Tool::OnActorEndOverlap);
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AS_Tool::OnEnemyOverlap);
}

// Called when the game starts or when spawned
void AS_Tool::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AS_Tool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (APengFu_PlayerCharacter* Char = Cast<APengFu_PlayerCharacter>(OverlappedActor))
	{
		if (PickupWidget->IsVisible()) 
		{
			WidgetRotation = FRotationMatrix::MakeFromX(Char->FollowCamera->GetComponentLocation() - PickupWidget->GetComponentLocation()).Rotator();
			PickupWidget->SetRelativeRotation(WidgetRotation);
		}

		if (PickupWidget->IsActive() && Char->bClubInInvenctory) {
			DeactivateComponents();
		}

	}
}

/*void AS_Tool::PostInitializeComponents()
{
	Super::PostInitializeComponents();


}*/

void AS_Tool::DeactivateComponents()
{
	PickupWidget->Deactivate();
	CollisionSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
}

void AS_Tool::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		if (APengFu_PlayerCharacter* Char = Cast<APengFu_PlayerCharacter>(OtherActor))
		{
			PickupWidget->SetVisibility(true);
			OverlappedActor = OtherActor;
			return;
		}
		return;
	}

}

void AS_Tool::OnActorEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		if (APengFu_PlayerCharacter* Char = Cast<APengFu_PlayerCharacter>(OtherActor))
		{
			PickupWidget->SetVisibility(false);
			return;
		}

		return;
	}
}

void AS_Tool::OnEnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		if (AS_AICharacter* AIChar = Cast<AS_AICharacter>(OtherActor))
		{
			AIChar->AttributeComp->ApplyHealthChange(-10);
			UGameplayStatics::PlaySoundAtLocation(this, AIChar->ImpactSound, GetActorLocation());
		}

		return;
	}
}

