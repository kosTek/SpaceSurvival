// Copyright Epic Games, Inc. All Rights Reserved.

#include "SpaceSurvivalProjectile.h"

#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

ASpaceSurvivalProjectile::ASpaceSurvivalProjectile() {

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));

	RootComponent = SceneComponent;
	
	// Set as root component
	RootComponent = SceneComponent;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = RootComponent;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 15.0f;
}

void ASpaceSurvivalProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit){
	UE_LOG(LogTemp, Warning, TEXT("[Projectile] Overlap!"));
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr)){

		UE_LOG(LogTemp, Warning, TEXT("[Projectile] Hit!"));
		
	}
	if (ProjectileMovement->bShouldBounce) {
		MaxBounces -= 1;
	}

	if (MaxBounces < 0) {
		Destroy();
	}
}