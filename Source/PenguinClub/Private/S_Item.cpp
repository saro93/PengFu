// Fill out your copyright notice in the Description page of Project Settings.

#include "S_Item.h"
#include "Components/BoxComponent.h"
#include "PengFu_PlayerCharacter.h"

// Sets default values
AS_Item::AS_Item()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemName = FString("Default");
	ItemCount = 0;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	SetRootComponent(ItemMesh);
	//CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	//CollisionBox->SetupAttachment(ItemMesh);
}

// Called when the game starts or when spawned
void AS_Item::BeginPlay()
{
	Super::BeginPlay();
}

void AS_Item::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}


// Called every frame
void AS_Item::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AS_Item::Interact_Implementation(APawn* InstigatorPawn)
{

}
