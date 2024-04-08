// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TopDownCharacter.generated.h"

class UCameraComponent;
class ATopDownTankProjectile;

UCLASS(Blueprintable)
class ATopDownCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATopDownCharacter();

	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }

	/** Fire this tank **/
	UFUNCTION(BlueprintCallable, Category = "Tank")
	void FireTank();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Tank Projectile")
	TSubclassOf<ATopDownTankProjectile> TankProjectileClass;

protected:
	/** Fire this tank in the server */
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_FireTank();

	UFUNCTION()
	void FireTank_Internal();

protected:
	/** Camera component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* TopDownCameraComponent;

	/** Location on gun mesh where projectiles should spawn */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	USceneComponent* MuzzleLocation;
};
