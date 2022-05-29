// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment.h"
#include "EquipmentWeapon.generated.h"

/**
 * 
 */

class ASpaceSurvivalProjectile;
class UAnimMontage;
class USoundWave;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSingleFire);

UCLASS()
class SPACESURVIVAL_API AEquipmentWeapon : public AEquipment {
	GENERATED_BODY()

public:

	AEquipmentWeapon();

	virtual void PrimaryFire() override;
	virtual void SecondaryFire() override;
	virtual void Reload() override;

	UPROPERTY(EditDefaultsOnly, Category = "Equipment")
	TSubclassOf<ASpaceSurvivalProjectile> ProjectileClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Equipment")
	UAnimMontage* SingleFireMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Equipment")
	USoundWave* SoundWave;

	UPROPERTY(BlueprintAssignable, Category = "Equipment")
	FOnSingleFire OnSingleFire;
	
};
