// Fill out your copyright notice in the Description page of Project Settings.


#include "SprintComponent.h"

#include <string>

// Sets default values for this component's properties
USprintComponent::USprintComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	MaxStamina = 100;
	Stamina = MaxStamina;

	StaminaDrainRate = 1;
	StaminaRecoveryRate = 1;

}


// Called when the game starts
void USprintComponent::BeginPlay(){
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USprintComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void USprintComponent::DrainStamina() {
	if (Stamina - StaminaDrainRate <= 0) {
		Stamina = 0;
	}else {
		Stamina -= StaminaDrainRate;
	}

	UE_LOG(LogTemp, Warning, TEXT("[Stamina] Draining at %d rate. Current stamina: %d"), StaminaDrainRate, Stamina);
}

void USprintComponent::RegenerateStamina() {
	if (Stamina < MaxStamina) {
		Stamina += StaminaRecoveryRate;
	}

	UE_LOG(LogTemp, Warning, TEXT("[Stamina] Recovering at %d rate. Current stamina: %d"), StaminaRecoveryRate, Stamina);
}

bool USprintComponent::CanSprint() {
	if (Stamina > 0) {
		return true;
	}

	return false;
}
