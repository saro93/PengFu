// Fill out your copyright notice in the Description page of Project Settings.


#include "PengFu_PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/EngineTypes.h"
#include "Components/TimelineComponent.h"
#include "Components/SphereComponent.h"
#include "PhysicsEngine/PhysicsSettings.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"
#include "S_InteractableComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "S_AttributeComponent.h"
#include "S_DynamicCollision_Component.h"
#include "Engine/World.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "S_Tool.h"
#include "S_Item.h"
#include "S_ActionComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APengFu_PlayerCharacter::APengFu_PlayerCharacter()
{

	PrimaryActorTick.bCanEverTick = true;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 250.f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	CameraBoom->SocketOffset = FVector(0, 10, 50);

	CollectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	CollectionSphere->SetupAttachment(RootComponent);
	CollectionSphere->SetSphereRadius(200);

	GetMesh()->SetupAttachment(RootComponent);

	InteractionComp = CreateDefaultSubobject<US_InteractableComponent>(TEXT("InteractionComponent"));
	AttributeComp = CreateDefaultSubobject<US_AttributeComponent>(TEXT("AttributeComp"));
	ActionComp = CreateDefaultSubobject<US_ActionComponent>(TEXT("ActionComp"));
	CollisionComp = CreateDefaultSubobject<US_DynamicCollision_Component>(TEXT("CollisionComp"));

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	bPrimaryAttack = false;
	bIsSprinting = false;
	JumpCount = 0;
	bEquip=false;
	bClubInInvenctory = false;

	speedLying = 300;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

}

void APengFu_PlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void APengFu_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (bClubInInvenctory) { EquipAction(); }
}

void APengFu_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void APengFu_PlayerCharacter::MoveForward(float Value)
{
	if (!bIsSliding) {
		GetCharacterMovement()->MaxWalkSpeed = 600;
		FRotator ControlRot = GetControlRotation();
		ControlRot.Pitch = 0.0f;
		ControlRot.Roll = 0.0f;
		AddMovementInput(ControlRot.Vector(), Value);
	}
	else if(!bBoostLoad && GetCharacterMovement()->GetLastUpdateVelocity().Size() <= 300)
	{
		FRotator ControlRot = GetControlRotation();
		ControlRot.Pitch = 0.0f;
		ControlRot.Roll = 0.0f;
		AddMovementInput(ControlRot.Vector(), Value);
		GetCharacterMovement()->MaxWalkSpeed = speedLying;
	}
}

void APengFu_PlayerCharacter::MoveRight(float Value)
{
	if (!bIsSliding) 
	{
		GetCharacterMovement()->MaxWalkSpeed = 600;
		FRotator ControlRot = GetControlRotation();
		ControlRot.Pitch = 0.0f;
		ControlRot.Roll = 0.0f;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
		AddMovementInput(RightVector, Value);
	}
	else if(!bBoostLoad && GetCharacterMovement()->GetLastUpdateVelocity().Size() <= 300 ) 
	{
		FRotator ControlRot = GetControlRotation();
		ControlRot.Pitch = 0.0f;
		ControlRot.Roll = 0.0f;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
		AddMovementInput(RightVector, Value);
		GetCharacterMovement()->MaxWalkSpeed = speedLying;
	}
	else if (!bBoostLoad && GetCharacterMovement()->GetLastUpdateVelocity().Size() > 300) 
	{
		LeanSlideDelta = Value;
		FRotator ControlRot = GetControlRotation();
		ControlRot.Pitch = 0.0f;
		ControlRot.Roll = 0.0f;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
		GetCharacterMovement()->MaxWalkSpeed = 0;
		AddMovementInput(RightVector, Value * 0.1);
	}

}


void APengFu_PlayerCharacter::PrimaryInteract()
{
	if (InteractionComp) { InteractionComp->PrimaryInteract(); }
}

void APengFu_PlayerCharacter::PickUpObjects()
{
	TArray<AActor*> InRangeItems;
	CollectionSphere->GetOverlappingActors(InRangeItems);

	for (int i = 0; i < InRangeItems.Num(); i++) 
	{
		if (!bClubInInvenctory) {
			if (AS_Tool* const Testitem = Cast<AS_Tool>(InRangeItems[i]))
			{
				bClubInInvenctory = true;
				EquippedWeapon = Testitem;
				EquippedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("BackWeaponOff"));
				EquippedWeapon->DeactivateComponents();
				break;
			}
		}
	}
}

void APengFu_PlayerCharacter::SprintStart()
{
	ActionComp->StartActionByName(this, "Sprint");
}
void APengFu_PlayerCharacter::SprintStop()
{
	ActionComp->StopActionByName(this, "Sprint");
}

AS_Tool* APengFu_PlayerCharacter::SpawnDefaultWeapon()
{
	if (StandardWeapon && bClubInInvenctory)
	{
		if (StandardWeapon) {
			bClubInInvenctory = true;
			return EquippedWeapon = GetWorld()->SpawnActor<AS_Tool>(StandardWeapon);
		}
		else return nullptr;
	}
	return nullptr;
}
void APengFu_PlayerCharacter::EquipAction()
{
	if (bClubInInvenctory && !bEquip)
	{
		bEquip = true;
		EquippedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("Pinna_R"));
	}
	else if (bClubInInvenctory && bEquip) {
		bEquip = false;
		EquippedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("BackWeaponOff"));
	}
}

void APengFu_PlayerCharacter::Slide()
{
	ActionComp->StartActionByName(this, "Slide");
}
void APengFu_PlayerCharacter::Slide_Stop()
{
	ActionComp->StopActionByName(this, "Slide");
}

void APengFu_PlayerCharacter::PrimaryAttack()
{
	ActionComp->StartActionByName(this,"PrimaryAttack");
}

void APengFu_PlayerCharacter::Jump()
{
	bJumpPressed = true;
	ActionComp->StartActionByName(this,"Jump");

}
void APengFu_PlayerCharacter::JumpStop()
{
	bJumpPressed = false;
	ActionComp->StopActionByName(this, "Jump");
}

void APengFu_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APengFu_PlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APengFu_PlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &APengFu_PlayerCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &APengFu_PlayerCharacter::SprintStart);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &APengFu_PlayerCharacter::SprintStop);

	PlayerInputComponent->BindAction("Slide",IE_Pressed,this,&APengFu_PlayerCharacter::Slide);
	PlayerInputComponent->BindAction("Slide", IE_Released, this, &APengFu_PlayerCharacter::Slide_Stop);


	PlayerInputComponent->BindAction("EquipWeapon", IE_Pressed,this, &APengFu_PlayerCharacter::EquipAction);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APengFu_PlayerCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APengFu_PlayerCharacter::JumpStop);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &APengFu_PlayerCharacter::PrimaryInteract);
	PlayerInputComponent->BindAction("PickUp", IE_Pressed, this, &APengFu_PlayerCharacter::PickUpObjects);
}

