// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "ItemEquipment.generated.h"

/**
 * 
 */

class UAnimMontage;

UCLASS()
class SPACESURVIVAL_API UItemEquipment : public UItem
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0.0))
	class UTexture2D* EquipmentSlotThumbnail;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0.0))
	class AEquipment* EquipmentReference;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	UAnimMontage* EquipAnimation;

protected:

	virtual void Use(ASpaceSurvivalCharacter* Player) override;
	
};
