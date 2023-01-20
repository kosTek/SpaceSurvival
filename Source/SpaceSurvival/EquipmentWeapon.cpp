// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentWeapon.h"

#include "SpaceSurvivalCharacter.h"
#include "SpaceSurvivalProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

AEquipmentWeapon::AEquipmentWeapon() {
	Reloading = false;
	ReloadTime = 1.f;

	MaxAmmo = 30;
	CurrentAmmo = MaxAmmo;

	NumberOfAmmoRemovedOnShot = 1;

	CanPlayEmptySound = true;
}

void AEquipmentWeapon::PrimaryFire() {

	if (ProjectileClass == nullptr){
		return;
	}

	if (!CanPrimary) {
		return;
	}

	if (Reloading) {
		return;
	}
	
	if (SingleFire) {
		OnSingleFire.Broadcast();
	}
	
	UWorld* const World = GetWorld();
	if (World != nullptr){
		APlayerController* PlayerController = Cast<APlayerController>(Player->GetController());
		const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
		const FVector SpawnLocation = this->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);

		//Set Spawn Collision Handling Override
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		if (CurrentAmmo <= 0) { // Ammo Check
			if (NoAmmoSound != nullptr && CanPlayEmptySound) {
				UGameplayStatics::PlaySound2D(this, NoAmmoSound);

				CanPlayEmptySound = false;
			}
		}else {
			World->SpawnActor<ASpaceSurvivalProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
			CurrentAmmo -= NumberOfAmmoRemovedOnShot;

			UGameplayStatics::PlaySound2D(this, SoundWave);
		}
		
		this->CanPrimary = false;
		GetWorld()->GetTimerManager().SetTimer(PrimaryFireDelayHandle, this, &AEquipmentWeapon::SetCanPrimary, PrimaryFireDelaySeconds, false);
	}
}

void AEquipmentWeapon::SecondaryFire() {
	
}

void AEquipmentWeapon::ReloadWeapon() {

	CurrentAmmo = MaxAmmo;

	CanPlayEmptySound = true;
	
	ChangeReloadingState();
}

void AEquipmentWeapon::Reload() {
	if (!Reloading) {
		OnReloadPressed.Broadcast();
		ChangeReloadingState();
		GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &AEquipmentWeapon::ReloadWeapon, ReloadTime, false);
		UE_LOG(LogTemp, Warning, TEXT("[Equipment] Weapon Reloading!"));
	}
}





