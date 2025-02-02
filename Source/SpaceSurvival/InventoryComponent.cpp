// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

#include "Item.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent(){
	GridSize = 20;

	EquipmentSlots.Add(nullptr);
	EquipmentSlots.Add(nullptr);
}


// Called when the game starts
void UInventoryComponent::BeginPlay(){
	Super::BeginPlay();

	for (auto& Item : DefaultItems) {
		AddItem(Item);
	}
	
}

bool UInventoryComponent::AddItem(UItem* Item, int Index) {

	if (!Item) {
		return false;
	}
	
	Item->Inventory = this;
	Item->World = GetWorld();
	if (Index != -1) {
		Item->Index = Index;
	}else {

		/*if() {
			
		}*/
		
		Item->Index = StoredItems.Num();
	}
	StoredItems.Add(Item);
	
	OnInventoryUpdated.Broadcast();

	UE_LOG(LogTemp, Warning, TEXT("Added item!"));
	
	return true;
}

bool UInventoryComponent::RemoveItem(UItem* Item) {
	if (Item) {
		Item->Inventory = nullptr;
		Item->World = nullptr;
		StoredItems.RemoveSingle(Item);
		OnInventoryUpdated.Broadcast();
		
		return true;
	}

	return false;
}

bool UInventoryComponent::RemoveItem(int ItemIndex) {
	if (ItemIndex >= 0 && ItemIndex < GridSize + 1) {

		//StoredItems[ItemIndex] = nullptr;
		
		for (int i = 0; i < StoredItems.Num(); i++) {
			if (StoredItems[i]->Index == ItemIndex) {
				StoredItems.RemoveSingle(StoredItems[i]);
			}
		}

		OnInventoryUpdated.Broadcast();

		// RemoveItem(StoredItems[ItemIndex]);
		
		return true;
	}

	return false;
}

bool UInventoryComponent::SwitchItems(int FromIndex, int ToIndex) {

	if (FromIndex >= 0 && ToIndex < GridSize + 1) {

		int FromItem = -1;
		int ToItem = -1;

		for (int i = 0; i < StoredItems.Num(); i++){
			if (StoredItems[i]->Index == FromIndex) {
				FromItem = i;
				UE_LOG(LogTemp, Warning, TEXT("[Inventory] Found FromItem index!"));
				break;
			}
		}

		for (int i = 0; i < StoredItems.Num(); i++){
			if (StoredItems[i]->Index == ToIndex) {
				ToItem = i;
				UE_LOG(LogTemp, Warning, TEXT("[Inventory] Found ToItem index!"));
				break;
			}
		}

		if (FromItem == -1) {
			return false;
		}

		StoredItems[FromItem]->Index = ToIndex;

		if (ToItem != -1) {
			StoredItems[ToItem]->Index = FromIndex;
		}
		
		return true;
	}

	UE_LOG(LogTemp, Warning, TEXT("[Inventory] Unable to change index!"));
	
	return false;
}

bool UInventoryComponent::SetEquipmentSlot(int index, class UItemEquipment* item, int itemIndex) {
	if (!item || index < 0 || index > 1) {
		return false;
	}
	
	EquipmentSlots[index] = item;

	UE_LOG(LogTemp, Warning, TEXT("[Inventory] Equipment slot set at %i index!"), index);
	
	OnEquipmentUpdated.Broadcast();

	RemoveItem(itemIndex);
	
	return true;
}

bool UInventoryComponent::SwitchEquipmentSlot(int FromIndex, int ToIndex) {
	if (FromIndex > 2 || FromIndex < 0) {
		return false;
	}

	if (ToIndex > 2 || ToIndex < 0) {
		return false;
	}

	if (FromIndex == ToIndex) {
		return false;
	}

	class UItemEquipment* Buffer = EquipmentSlots[FromIndex];

	EquipmentSlots[FromIndex] = EquipmentSlots[ToIndex];
	EquipmentSlots[ToIndex] = Buffer;

	OnEquipmentUpdated.Broadcast();
	
	return true;
}

bool UInventoryComponent::ClearEquipmentSlot(int index) {

	if (index < 0 || index > 1) {
		return false;
	}

	EquipmentSlots[index] = nullptr;
	
	OnEquipmentUpdated.Broadcast();

	return true;
}



