// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentWeapon.h"

#include "SpaceSurvivalCharacter.h"
#include "SpaceSurvivalProjectile.h"

AEquipmentWeapon::AEquipmentWeapon() {
	
}

void AEquipmentWeapon::PrimaryFire() {
	if (!CanPrimary) {
		return;
	}

	if (SingleFire) {
		OnSingleFire.Broadcast();
	}
	
	if (ProjectileClass != nullptr){
		UWorld* const World = GetWorld();
		if (World != nullptr){
			APlayerController* PlayerController = Cast<APlayerController>(Player->GetController());
			const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = this->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);
	
			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	
			// Spawn the projectile at the muzzle
			World->SpawnActor<ASpaceSurvivalProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);

			this->CanPrimary = false;
			GetWorld()->GetTimerManager().SetTimer(PrimaryFireDelayHandle, this, &AEquipmentWeapon::SetCanPrimary, PrimaryFireDelaySeconds, false);
		}
	}
}

void AEquipmentWeapon::SecondaryFire() {
	
}

void AEquipmentWeapon::Reload() {
	
}



