// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemFood.h"

#include "NeedsComponent.h"
#include "SpaceSurvivalCharacter.h"

void UItemFood::Use(ASpaceSurvivalCharacter* Player) {
	if (Player) {
		Player->NeedsComponent->ChangeFood(FoodValue);
	}
}
