// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment.h"
#include "EquipmentWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SPACESURVIVAL_API AEquipmentWeapon : public AEquipment {
	GENERATED_BODY()

public:

	AEquipmentWeapon();

	virtual void PrimaryFire() override;
	virtual void SecondaryFire() override;
	virtual void Reload() override;
	
};
