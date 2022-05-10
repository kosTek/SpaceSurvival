// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class SPACESURVIVAL_API UItem : public UObject{
	GENERATED_BODY()

public:
	
	UItem();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FText UseText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	class UStaticMesh* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	class UTexture2D* Thumbnail;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FText ItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (MultiLine = true))
	FText ItemDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 1.0))
	int Amount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	int Index;

	UPROPERTY()
	class UInventoryComponent* Inventory;

	virtual void Use(class ASpaceSurvivalCharacter* Player) PURE_VIRTUAL(UItem);

	UFUNCTION(BlueprintImplementableEvent)
	void OnUse(class ASpaceSurvivalCharacter* Player);

	UPROPERTY()
	class UWorld* World;
	
};
