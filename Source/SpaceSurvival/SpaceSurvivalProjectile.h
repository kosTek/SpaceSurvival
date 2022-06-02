// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpaceSurvivalProjectile.generated.h"

class UBoxComponent;
class USceneComponent;
class UProjectileMovementComponent;

UCLASS(config=Game)
class ASpaceSurvivalProjectile : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Projectile")
	USceneComponent* SceneComponent;

public:
	ASpaceSurvivalProjectile();

	/** Projectile movement component */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;
	
	/** called when projectile hits something */
	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile")
	int MaxBounces;
	
};

