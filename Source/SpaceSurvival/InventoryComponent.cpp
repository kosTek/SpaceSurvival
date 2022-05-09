// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

#include "Item.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent(){
	GridSize = 28;
}


// Called when the game starts
void UInventoryComponent::BeginPlay(){
	Super::BeginPlay();

	for (auto& Item : DefaultItems) {
		AddItem(Item);
	}
	
}

bool UInventoryComponent::AddItem(UItem* Item) {

	if (!Item) {
		return false;
	}
	
	Item->Inventory = this;
	Item->World = GetWorld();
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

		StoredItems[ItemIndex] = nullptr;
		
		OnInventoryUpdated.Broadcast();
		
		return true;
	}

	return false;
}

bool UInventoryComponent::SwitchItems(int FromIndex, int ToIndex) {

	auto Item = StoredItems[FromIndex];
	auto SwitchedItem = StoredItems[ToIndex];

	StoredItems[FromIndex] = SwitchedItem;
	StoredItems[ToIndex] = Item;

	OnInventoryUpdated.Broadcast();
	
	return false;
}


