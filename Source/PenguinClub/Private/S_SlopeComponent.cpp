// Fill out your copyright notice in the Description page of Project Settings.


#include "S_SlopeComponent.h"
#include "PengFu_PlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

// Sets default values for this component's properties
US_SlopeComponent::US_SlopeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	DefaultMeshLocation = FVector(0.f, 0.f, -60.f);

	SlidingMeshLocation = FVector(-15, 0, -40);
	// ...
}


// Called when the game starts
void US_SlopeComponent::BeginPlay()
{
	Super::BeginPlay();

	Character = Cast<APengFu_PlayerCharacter>(GetOwner());
	// ...
}


// Called every frame
void US_SlopeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Character)
	{


		//MESH ROTATION BASED ON FLOOR ANGLE WHEN SLIDING
		if (Character->bIsSliding) {

			FName LowerBone = "TraceLow_Loc";

			FVector LowerLocation = Character->GetMesh()->GetSocketLocation(LowerBone) + FVector(0, 0, 20);

			FHitResult HitResultLow; // Trace LowerBody

			FCollisionQueryParams TraceParams(FName(TEXT("UpperBody_FloorTrace")), true, Character);
			TraceParams.bTraceComplex = false;
			TraceParams.bReturnPhysicalMaterial = false;
			TraceParams.AddIgnoredActor(Character);

			bool bHitLower = GetWorld()->LineTraceSingleByChannel(HitResultLow, LowerLocation, LowerLocation + FVector(0, 0, -1000), ECC_Visibility, TraceParams);

			if (bHitLower)
			{
				// Get the normal of the floor at the player's location
				FVector FloorNormal = HitResultLow.ImpactNormal;
				//UE_LOG(LogTemp, Warning, TEXT("The NormalUp value is: %f"), FloorNormal.X);

				// Get the angle of the floor
				FloorAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(FVector(0, 0, 1), FloorNormal)));

				CharacterLocation = Character->GetActorLocation();

				if (FloorAngle >= 0 && FloorAngle < 10)
				{
					NewRotation = FRotator(0, -90, 0);
					SlidingMeshLocation = FVector(-15, 0, -40);
				}
				else if (FloorAngle >= 10 && FloorAngle < 30)
				{
					if (CharacterLocation.Z > PreviousCharacterLocation.Z && CharacterLocation.Z != PreviousCharacterLocation.Z) {// Going Up
						NewRotation = FRotator(0, -90, -20);
						SlidingMeshLocation = FVector(-5, 0, -45);
					}
					else if (CharacterLocation.Z != PreviousCharacterLocation.Z) {// Going Down
						NewRotation = FRotator(0, -90, 14);
						SlidingMeshLocation = FVector(-20, 0, -35);
					}
				}
				else if (FloorAngle >= 30 && FloorAngle <= 45)
				{
					if (CharacterLocation.Z > PreviousCharacterLocation.Z && CharacterLocation.Z != PreviousCharacterLocation.Z) {// Going Up
						NewRotation = FRotator(0, -90, -35);
						SlidingMeshLocation = FVector(10, 0, -40);
					}
					else if (CharacterLocation.Z != PreviousCharacterLocation.Z) { // Going Down
						NewRotation = FRotator(0, -90, 35);
						SlidingMeshLocation = FVector(-30, 0, -30);
					}
				}

				// Interpolate the rotation of the mesh to match the angle of the floor
				FRotator InterpolatedRotation = FMath::RInterpTo(Character->GetMesh()->GetRelativeRotation(), NewRotation, DeltaTime, 10);
				FVector InterpolationLocation = FMath::VInterpTo(Character->GetMesh()->GetRelativeLocation(), SlidingMeshLocation, DeltaTime, 10);
				Character->GetMesh()->SetRelativeRotation(InterpolatedRotation);
				Character->GetMesh()->SetRelativeLocation(InterpolationLocation);

				PreviousCharacterLocation = CharacterLocation;
			}
		}
		else if (Character->GetMesh()->GetRelativeRotation() != FRotator(0, -90, 0) && !Character->GetCharacterMovement()->IsFalling() && !Character->bIsSwimming)
		{
			NewRotation = FRotator(0, -90, 0);
			FRotator InterpolatedRotation = FMath::RInterpTo(Character->GetMesh()->GetRelativeRotation(), NewRotation, DeltaTime, 10);
			FVector InterpolationLocation = FMath::VInterpTo(Character->GetMesh()->GetRelativeLocation(), DefaultMeshLocation, DeltaTime, 10);
			Character->GetMesh()->SetRelativeRotation(InterpolatedRotation);
			Character->GetMesh()->SetRelativeLocation(InterpolationLocation);
		}
	}
}
	// ...

