// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEquipmentUpdated);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACESURVIVAL_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	// Inventory
	bool AddItem(class UItem* Item, int Index = -1);
	bool RemoveItem(class UItem* Item);

	UFUNCTION(BlueprintCallable)
	bool RemoveItem(int ItemIndex);

	UFUNCTION(BlueprintCallable)
	bool SwitchItems(int FromIndex, int ToIndex);
	
	UPROPERTY(EditDefaultsOnly, Instanced)
	TArray<class UItem*> DefaultItems;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	int GridSize;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryUpdated OnInventoryUpdated;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
	TArray<class UItem*> StoredItems;

	// Equipment
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnEquipmentUpdated OnEquipmentUpdated;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
	TArray<class AEquipment*> EquipmentSlots;
	
	UFUNCTION(BlueprintCallable)
	bool SetEquipmentSlot(int index, class AEquipment* item);
	
	UFUNCTION(BlueprintCallable)
	bool ClearEquipmentSlot(int index);
	
};
