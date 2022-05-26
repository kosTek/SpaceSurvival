// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "ItemEquipment.generated.h"

/**
 * 
 */
UCLASS()
class SPACESURVIVAL_API UItemEquipment : public UItem
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equipment", meta = (ClampMin = 0.0))
	class UItemEquipment* EquipmentReference;
	
protected:

	virtual void Use(ASpaceSurvivalCharacter* Player) override;
	
};
