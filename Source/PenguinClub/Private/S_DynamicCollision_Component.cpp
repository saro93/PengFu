// Fill out your copyright notice in the Description page of Project Settings.


#include "S_DynamicCollision_Component.h"
#include "PengFu_PlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
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

	JumpingMeshLocation = FVector(0, 0, -80);

	SwimmingMeshLocation = FVector(0,1,-35);
	// ...
}


// Called when the game starts
void US_DynamicCollision_Component::BeginPlay()
{
	Super::BeginPlay();

	// Syestem for change the capsule size in accord of the animation slide
		FOnTimelineFloat Sliding_Update;
		Sliding_Update.BindUFunction(this, FName("SlideUpdate"));

		FOnTimelineFloat Jumping_Update;
		Jumping_Update.BindUFunction(this, FName("JumpUpdate"));

		FOnTimelineFloat Swimming_Update;
		Swimming_Update.BindUFunction(this, FName("SwimUpdate"));

		FOnTimelineEvent SlideFinishedEvent;
		SlideFinishedEvent.BindUFunction(this, FName("ActionFinish"));
		
		FOnTimelineEvent JumpFinishedEvent;
		JumpFinishedEvent.BindUFunction(this, FName("ActionFinish"));

		FOnTimelineEvent SwimFinishedEvent;
		SwimFinishedEvent.BindUFunction(this, FName("ActionFinish"));

		SlidingTime.AddInterpFloat(SlidingCurve, Sliding_Update);
		SlidingTime.SetTimelineFinishedFunc(SlideFinishedEvent);

		JumpingTime.AddInterpFloat(SlidingCurve, Jumping_Update);
		JumpingTime.SetTimelineFinishedFunc(JumpFinishedEvent);

		SwimmingTime.AddInterpFloat(SlidingCurve, Swimming_Update);
		SwimmingTime.SetTimelineFinishedFunc(SwimFinishedEvent);

		Character = Cast<APengFu_PlayerCharacter>(GetOwner());

}


// Called every frame
void US_DynamicCollision_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	JumpingTime.TickTimeline(DeltaTime);
	SlidingTime.TickTimeline(DeltaTime);
	SwimmingTime.TickTimeline(DeltaTime);

	if (Character) {


		if (!Character->GetCharacterMovement()->IsFalling() && !Character->bIsSliding && !Character->bIsSwimming)
		{
			JumpingTime.Reverse();
		}

		// SURFACE MATERIAL DETECTION
		FHitResult HitResultSurfaceDetection;
		FCollisionResponseParams ResponseSurface;
		FVector StartTraceSurface = Character->GetActorLocation();
		FVector EndSurfaceTrace = StartTraceSurface + FVector(0, 0, -65);
		FCollisionQueryParams TraceSurfaceParams(FName(TEXT("TraceCharacter_SurfaceDetection")), true, Character);
		TraceSurfaceParams.bReturnPhysicalMaterial = true;
		TraceSurfaceParams.AddIgnoredActor(Character);

		bool bHitSurface = GetWorld()->LineTraceSingleByChannel(HitResultSurfaceDetection, StartTraceSurface, EndSurfaceTrace, ECollisionChannel::ECC_Visibility, TraceSurfaceParams, ResponseSurface);

		//DrawDebugLine(GetWorld(), StartTraceSurface, EndSurfaceTrace, FColor::Silver,false,1);

		if (bHitSurface && HitResultSurfaceDetection.PhysMaterial != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("The Sur is: "));
			if (HitResultSurfaceDetection.PhysMaterial->SurfaceType == SurfaceType2)
			{
				Character->bIsSwimming = true;
				SwimmingTime.Play();
			}
			else if(!Character->GetCharacterMovement()->IsFalling() && !Character->bIsSliding && !SlidingTime.IsPlaying() && !JumpingTime.IsReversing()) {
				Character->bIsSwimming = false;
				SwimmingTime.Reverse();
			}
		}

		//MESH ROTATION BASED ON FLOOR ANGLE WHEN SLIDING
		if (Character->bIsSliding) {

			FName LowerBone = "TraceLow_Loc";

			FVector LowerLocation = Character->GetMesh()->GetSocketLocation(LowerBone) + FVector(0,0,20);

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

void US_DynamicCollision_Component::SlideUpdate(float Alpha)
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

void US_DynamicCollision_Component::JumpUpdate(float Alpha)
{
	if (Character)
	{
		float NewHalfHeight = FMath::Lerp(DefaultCapsuleHalfHeight, JumpingCapsuleHalfHeight, Alpha);
		Character->GetCapsuleComponent()->SetCapsuleHalfHeight(NewHalfHeight);

		float NewRadius = FMath::Lerp(DefaultCapsuleRadius, JumpingCapsuleRadius, Alpha);
		Character->GetCapsuleComponent()->SetCapsuleRadius(NewRadius);

		FVector LocationMesh = FMath::Lerp(DefaultMeshLocation, JumpingMeshLocation, Alpha);
		Character->GetMesh()->SetRelativeLocation(LocationMesh);
	}
}

void US_DynamicCollision_Component::SwimUpdate(float Alpha)
{
	if (Character) 
	{
		float NewHalfHeight = FMath::Lerp(DefaultCapsuleHalfHeight, SwimmingCapsuleHalfHeight, Alpha);
		Character->GetCapsuleComponent()->SetCapsuleHalfHeight(NewHalfHeight);

		float NewRadius = FMath::Lerp(DefaultCapsuleRadius, SwimmingCapsuleRadius, Alpha);
		Character->GetCapsuleComponent()->SetCapsuleRadius(NewRadius);

		FVector LocationMesh = FMath::Lerp(DefaultMeshLocation, SwimmingMeshLocation, Alpha);
		Character->GetMesh()->SetRelativeLocation(LocationMesh);
	}
}

void US_DynamicCollision_Component::ActionFinish()
{
}

