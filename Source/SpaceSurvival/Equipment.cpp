// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment.h"

#include "SpaceSurvivalCharacter.h"

// Sets default values
AEquipment::AEquipment(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CanPrimary = true;

	PrimaryFireDelaySeconds = 1.f;
	
}

// Called when the game starts or when spawned
void AEquipment::BeginPlay(){
	Super::BeginPlay();
	
}

// Called every frame
void AEquipment::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}

void AEquipment::PrimaryFire() {
	
}

void AEquipment::SecondaryFire() {
	
}

void AEquipment::Reload() {
	
}

void AEquipment::ChangeReloadingState() {
	Reloading = !Reloading;
	UE_LOG(LogTemp, Warning, TEXT("[Equipment] Weapon Reload State Changed!"));
}

void AEquipment::OnEquipmentSpawn(ASpaceSurvivalCharacter* Character) {
	if (Character != nullptr) {
		Player = Character;

		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
		//GetOwner()->AttachToComponent(Player->Mesh1P, AttachmentRules, FName(TEXT("Right_Socket")));

		this->AttachToComponent(Player->Mesh1P, AttachmentRules, FName(TEXT("Right_Socket")));

		Player->OnPrimaryFire.AddDynamic(this, &AEquipment::PrimaryFire);  
		Player->OnSecondaryFire.AddDynamic(this, &AEquipment::SecondaryFire);
		Player->OnReload.AddDynamic(this, &AEquipment::Reload);

		Player->SetCurrentEquipment(this);
		
		UE_LOG(LogTemp, Warning, TEXT("[Equipment] OnEquipmentSpawn called successfully!"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("[Equipment] Character is NULL"));
	}
}

void AEquipment::OnEquipmentDespawn() {
	
}

void AEquipment::SetCanPrimary() {
	CanPrimary = true;
}


