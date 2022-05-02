// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NeedsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACESURVIVAL_API UNeedsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNeedsComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Max Value
	
	UPROPERTY(EditAnywhere)
	float MaxFood;

	UPROPERTY(EditAnywhere)
	float MaxWater;

	UPROPERTY(EditAnywhere)
	float MaxOxygen;

	// Changing Value
	
	UPROPERTY(EditAnywhere)
	float Food;

	UPROPERTY(EditAnywhere)
	float Water;

	UPROPERTY(EditAnywhere)
	float Oxygen;

	// Drain Value

	UPROPERTY(EditAnywhere)
	float FoodDrainRate;

	UPROPERTY(EditAnywhere)
	float WaterDrainRate;

	UPROPERTY(EditAnywhere)
	float OxygenDrainRate;

	// Functions
	
	UFUNCTION(BlueprintCallable)
	void ChangeFood(float value);

	UFUNCTION(BlueprintCallable)
	void ChangeWater(float value);

	UFUNCTION(BlueprintCallable)
	void ChangeOxygen(float value);

		// Draining Stuff
	
	UFUNCTION()
	void DrainNeeds();

	UPROPERTY()
	FTimerHandle DrainHandle;

	UPROPERTY()
	float DrainEverySeconds;
	
	
};
