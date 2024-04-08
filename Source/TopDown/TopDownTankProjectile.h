// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TopDownTankProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class TOPDOWN_API ATopDownTankProjectile : public AActor
{
	GENERATED_BODY()

public:
	ATopDownTankProjectile();

	UFUNCTION()
	void OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	/** Projectile mesh. Used only for visuals */
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	UStaticMeshComponent* MeshComp;

	/** Projectile collision component. Used for collision detection */
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComp;

	/** Tank Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;
};
