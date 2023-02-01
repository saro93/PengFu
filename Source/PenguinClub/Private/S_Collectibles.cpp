// Fill out your copyright notice in the Description page of Project Settings.


#include "S_Collectibles.h"
#include "Components/CapsuleComponent.h"
#include "PengFu_PlayerCharacter.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AS_Collectibles::AS_Collectibles()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	Mesh->SetCollisionResponseToAllChannels(ECR_Overlap);

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AS_Collectibles::OnActorBeginOverlap);

	Amount = 0;
}

// Called when the game starts or when spawned
void AS_Collectibles::BeginPlay()
{
	Super::BeginPlay();
	
}

void AS_Collectibles::OnActorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APengFu_PlayerCharacter* Character = Cast<APengFu_PlayerCharacter>(OtherActor);

	if (!Character) {
		return;
	}
	if(OtherComp == Character->GetCapsuleComponent())
	{
		Amount += 1;
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
        Destroy();
		UE_LOG(LogTemp, Warning, TEXT("The integer value is: %d"), Amount);
	}
}
	

void AS_Collectibles::OnActorEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

// Called every frame
void AS_Collectibles::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

