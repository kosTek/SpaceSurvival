// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SprintComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACESURVIVAL_API USprintComponent : public UActorComponent{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USprintComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
	int MaxStamina;
	
	UPROPERTY(EditAnywhere)
	int Stamina;

	UPROPERTY(EditAnywhere)
	int StaminaDrainRate;

	UPROPERTY(EditAnywhere)
	int StaminaRecoveryRate;

	UPROPERTY(EditAnywhere)
	int SprintModifier;
	
	UFUNCTION()
	void DrainStamina();

	UFUNCTION()
	void RegenerateStamina();

	UFUNCTION()
	bool CanSprint();
	
};
