// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

class APlayerController;
class ATopDownCharacter;

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TopDownGameMode.generated.h"

UCLASS(minimalapi)
class ATopDownGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATopDownGameMode();

	/** Moves the player back to a player start */
	UFUNCTION(BlueprintCallable, Category = Respawn)
	void RespawnPlayer(APlayerController* PlayerController);

	/** */
	UFUNCTION(BlueprintCallable, Category = "Game rules")
	void ProjectileHit(ATopDownCharacter* HitCharacter, ATopDownCharacter* InstigatorCharacter);
};



