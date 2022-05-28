// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Equipment.generated.h"

class UStaticMesh;
class ASpaceSurvivalCharacter;

UCLASS()
class SPACESURVIVAL_API AEquipment : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEquipment();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equipment")
	UStaticMesh* StaticMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equipment")
	FName EquipmentName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equipment")
	int EquipmentID;
	
	UPROPERTY()
	ASpaceSurvivalCharacter* Player;
	
	UFUNCTION()
	virtual void PrimaryFire();

	UFUNCTION()
	virtual void SecondaryFire();

	UFUNCTION()
	virtual void Reload();

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void OnEquipmentSpawn(ASpaceSurvivalCharacter* Character);

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void OnEquipmentDespawn();
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnPrimaryFire();

	UFUNCTION(BlueprintImplementableEvent)
	void OnSecondaryFire();

	UFUNCTION(BlueprintImplementableEvent)
	void OnReload();
	
	
	
};
