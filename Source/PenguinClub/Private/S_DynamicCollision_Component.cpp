// Fill out your copyright notice in the Description page of Project Settings.


#include "S_DynamicCollision_Component.h"
#include "PengFu_PlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"
#include "Engine.h"
#include "Components/TimelineComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values for this component's properties
US_DynamicCollision_Component::US_DynamicCollision_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	DefaultCapsuleHalfHeight = 60.f;

	DefaultCapsuleRadius = 24.5f;

	DefaultMeshLocation = FVector(0.f, 0.f, -60.f);

	SlidingMeshLocation = FVector(-15, 0, -40);
	// ...
}


// Called when the game starts
void US_DynamicCollision_Component::BeginPlay()
{
	Super::BeginPlay();

	// Syestem for change the capsule size in accord of the animation slide
		FOnTimelineFloat ProgressUpdate;
		ProgressUpdate.BindUFunction(this, FName("ActionUpdate"));

		FOnTimelineEvent FinishedEvent;
		FinishedEvent.BindUFunction(this, FName("ActionFinish"));

		SlidingTime.AddInterpFloat(SlidingCurve, ProgressUpdate);
		SlidingTime.SetTimelineFinishedFunc(FinishedEvent);

		Character = Cast<APengFu_PlayerCharacter>(GetOwner());

}


// Called every frame
void US_DynamicCollision_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	SlidingTime.TickTimeline(DeltaTime);
	// ...


	if (Character) {
		if (Character->bIsSliding) {

			FName UpperBone = "Spine_2";
			FName LowerBone = "TraceLow_Loc";

			// Get the player's current location
			//FVector UpperLocation = Character->GetMesh()->GetBoneLocation(UpperBone);
			FVector LowerLocation = Character->GetMesh()->GetSocketLocation(LowerBone) + FVector(0,0,20);

			// Trace a line down from the player's location to the floor
			//FHitResult HitResultUp; // trace UpperBody
			FHitResult HitResultLow; // Trace LowerBody

			FCollisionQueryParams TraceParams(FName(TEXT("UpperBody_FloorTrace")), true, Character);
			TraceParams.bTraceComplex = false;
			TraceParams.bReturnPhysicalMaterial = false;
			TraceParams.AddIgnoredActor(Character);

			//bool bHitUpper = GetWorld()->LineTraceSingleByChannel(HitResultUp, UpperLocation, UpperLocation + FVector(0, 0, -1000), ECC_Visibility, TraceParams);
			bool bHitLower = GetWorld()->LineTraceSingleByChannel(HitResultLow, LowerLocation, LowerLocation + FVector(0, 0, -1000), ECC_Visibility, TraceParams);

			if (bHitLower)
			{

				// Get the normal of the floor at the player's location
				//FVector FloorNormalUp = HitResultUp.ImpactNormal;
				//UE_LOG(LogTemp, Warning, TEXT("The NormalUp value is: %f"), FloorNormalUp.X);

				// Get the angle of the floor
				//FloorAngleUp = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(FVector(0, 0, 1), FloorNormalUp)));
				//UE_LOG(LogTemp, Warning, TEXT("The AngleUp value is: %f"), FloorAngleUp);

				// Get the normal of the floor at the player's location
				FVector FloorNormal = HitResultLow.ImpactNormal;
				//UE_LOG(LogTemp, Warning, TEXT("The NormalUp value is: %f"), FloorNormal.X);

				// Get the angle of the floor
				FloorAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(FVector(0, 0, 1), FloorNormal)));
				//UE_LOG(LogTemp, Warning, TEXT("The AngleUp value is: %f"), FloorAngle);

				// Get the normal of the floor at the player's location
				//FVector FloorNormalLow = HitResultLow.ImpactNormal;
				//UE_LOG(LogTemp, Warning, TEXT("The NormalLow value is: %f"), FloorNormalLow.X);

				// Get the angle of the floor
				//FloorAngleLow = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(FVector(0, 0, 1), FloorNormalLow)));
				//UE_LOG(LogTemp, Warning, TEXT("The AngleLow value is: %f"), FloorAngleLow);

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

				//DrawDebugLine(GetWorld(), UpperLocation, HitResultUp.Location, FColor::Red, false, -1, 0, 12.000);
				//DrawDebugPoint(GetWorld(), HitResultUp.Location, 5.f, FColor::Green, false, 2.f);

				//DrawDebugLine(GetWorld(), LowerLocation, HitResultLow.Location, FColor::Red, false, -1, 0, 12.000);
				//DrawDebugPoint(GetWorld(), HitResultLow.Location, 5.f, FColor::Green, false, 2.f);
			}
		}
		else if (Character->GetMesh()->GetRelativeRotation() != FRotator(0, -90, 0))
		{
			NewRotation = FRotator(0, -90, 0);
			FRotator InterpolatedRotation = FMath::RInterpTo(Character->GetMesh()->GetRelativeRotation(), NewRotation, DeltaTime, 10);
			FVector InterpolationLocation = FMath::VInterpTo(Character->GetMesh()->GetRelativeLocation(), DefaultMeshLocation, DeltaTime, 10);
			Character->GetMesh()->SetRelativeRotation(InterpolatedRotation);
			Character->GetMesh()->SetRelativeLocation(InterpolationLocation);
		}
	}
}

void US_DynamicCollision_Component::ActionUpdate(float Alpha)
{
	if (Character)
	{
		float NewHalfHeight = FMath::Lerp(DefaultCapsuleHalfHeight, SlidingCapsuleHalfHeight, Alpha);
		Character->GetCapsuleComponent()->SetCapsuleHalfHeight(NewHalfHeight);

		float NewRadius = FMath::Lerp(DefaultCapsuleRadius, SlidingCapsuleRadius, Alpha);
		Character->GetCapsuleComponent()->SetCapsuleRadius(NewRadius);

		FVector LocationMesh = FMath::Lerp(DefaultMeshLocation, SlidingMeshLocation, Alpha);
		Character->GetMesh()->SetRelativeLocation(LocationMesh);
	}
}

void US_DynamicCollision_Component::ActionFinish()
{



}

