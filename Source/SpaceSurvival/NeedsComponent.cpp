// Fill out your copyright notice in the Description page of Project Settings.


#include "NeedsComponent.h"
#include "TimerManager.h"

// Sets default values for this component's properties
UNeedsComponent::UNeedsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	MaxFood = 100.f;
	MaxWater = 100.f;
	MaxOxygen = 100.f;

	Food = MaxFood;
	Water = MaxWater;
	Oxygen = MaxOxygen;

	FoodDrainRate = 1.f;
	WaterDrainRate = 1.f;
	OxygenDrainRate = 1.f;

	DrainEverySeconds = 2.f;
	
}


// Called when the game starts
void UNeedsComponent::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(DrainHandle, this, &UNeedsComponent::DrainNeeds, DrainEverySeconds, true, 1.f);
	
}


// Called every frame
void UNeedsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UNeedsComponent::ChangeFood(float value) {
	Food += value;
}

void UNeedsComponent::ChangeWater(float value) {
	Water += value;
}

void UNeedsComponent::ChangeOxygen(float value) {
	Oxygen += value;
}

void UNeedsComponent::DrainNeeds() {
	UE_LOG(LogTemp, Warning, TEXT("[Needs] Drain Called"));
}



