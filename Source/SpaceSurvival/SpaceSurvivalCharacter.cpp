// Copyright Epic Games, Inc. All Rights Reserved.

#include "SpaceSurvivalCharacter.h"

#include "NeedsComponent.h"
#include "SpaceSurvivalProjectile.h"
#include "SprintComponent.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/InputSettings.h"


//////////////////////////////////////////////////////////////////////////
// ASpaceSurvivalCharacter

ASpaceSurvivalCharacter::ASpaceSurvivalCharacter(){

	PrimaryActorTick.bCanEverTick = true;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	TurnRateGamepad = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	// Sprint
	SprintComponent = CreateDefaultSubobject<USprintComponent>(TEXT("SprintComponent"));
	CanSprint = true;
	IsSprinting = false;

	SprintModifier = 2;

	NormalSpeed = this->GetCharacterMovement()->MaxWalkSpeed;
	MaxSprintSpeed = NormalSpeed * SprintModifier;

	// Needs

	NeedsComponent = CreateDefaultSubobject<UNeedsComponent>(TEXT("NeedsComponent"));
	
}

void ASpaceSurvivalCharacter::BeginPlay(){
	// Call the base class  
	Super::BeginPlay();

}

void ASpaceSurvivalCharacter::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	CanSprint = SprintComponent->CanSprint();

	if (IsSprinting) {
		SprintComponent->DrainStamina();
		if (CanSprint) {
			this->GetCharacterMovement()->MaxWalkSpeed = MaxSprintSpeed;
		}else {
			this->GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
		}
	}else {
		SprintComponent->RegenerateStamina();
		this->GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
	}
}


//////////////////////////////////////////////////////////////////////////// Input

void ASpaceSurvivalCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent){
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("PrimaryAction", IE_Pressed, this, &ASpaceSurvivalCharacter::OnPrimaryAction);

	// Enable touchscreen input
	EnableTouchscreenMovement(PlayerInputComponent);

	// Bind movement events
	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &ASpaceSurvivalCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &ASpaceSurvivalCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "Mouse" versions handle devices that provide an absolute delta, such as a mouse.
	// "Gamepad" versions are for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &ASpaceSurvivalCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &ASpaceSurvivalCharacter::LookUpAtRate);

	//Sprint
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ASpaceSurvivalCharacter::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ASpaceSurvivalCharacter::StopSprint);
}

void ASpaceSurvivalCharacter::OnPrimaryAction(){
	// Trigger the OnItemUsed Event
	OnUseItem.Broadcast();
}

void ASpaceSurvivalCharacter::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location){
	if (TouchItem.bIsPressed == true){
		return;
	}
	if ((FingerIndex == TouchItem.FingerIndex) && (TouchItem.bMoved == false)){
		OnPrimaryAction();
	}
	TouchItem.bIsPressed = true;
	TouchItem.FingerIndex = FingerIndex;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;
}

void ASpaceSurvivalCharacter::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location){
	if (TouchItem.bIsPressed == false){
		return;
	}
	TouchItem.bIsPressed = false;
}

void ASpaceSurvivalCharacter::MoveForward(float Value){
	if (Value != 0.0f){
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value * 50);
	}
}

void ASpaceSurvivalCharacter::MoveRight(float Value){
	if (Value != 0.0f){
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ASpaceSurvivalCharacter::TurnAtRate(float Rate){
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void ASpaceSurvivalCharacter::LookUpAtRate(float Rate){
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

bool ASpaceSurvivalCharacter::EnableTouchscreenMovement(class UInputComponent* PlayerInputComponent){
	if (FPlatformMisc::SupportsTouchInput() || GetDefault<UInputSettings>()->bUseMouseForTouch){
		PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ASpaceSurvivalCharacter::BeginTouch);
		PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &ASpaceSurvivalCharacter::EndTouch);

		return true;
	}
	
	return false;
}

void ASpaceSurvivalCharacter::Sprint() {
	IsSprinting = true;
}

void ASpaceSurvivalCharacter::StopSprint() {
	IsSprinting = false;
}

