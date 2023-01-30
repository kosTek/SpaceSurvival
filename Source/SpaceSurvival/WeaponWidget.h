// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WeaponWidget.generated.h"

class UTextBlock;

UCLASS()
class SPACESURVIVAL_API UWeaponWidget : public UUserWidget{
	GENERATED_BODY()

public:

	void SetCurrentAmmo(int Ammo);

	void SetCurrentMaxAmmo(int Ammo);
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UTextBlock* CurrentAmmo;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UTextBlock* MaxAmmo;
	
};
