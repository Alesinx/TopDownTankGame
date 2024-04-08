// Copyright Epic Games, Inc. All Rights Reserved.

#include "TopDownGameMode.h"
#include "Gameframework/PlayerController.h"
#include "Gameframework/PlayerState.h"
#include "TopDownPlayerController.h"
#include "TopDownPlayerState.h"
#include "TopDownCharacter.h"
#include "Gameframework/PlayerState.h"
#include "UObject/ConstructorHelpers.h"

ATopDownGameMode::ATopDownGameMode()
{
	PlayerControllerClass = ATopDownPlayerController::StaticClass();

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerState> PlayerStateBPClass(TEXT("/Game/BP_TopDownPlayerState"));
	if (PlayerStateBPClass.Class != NULL)
	{
		PlayerStateClass = PlayerStateBPClass.Class;
	}
}

void ATopDownGameMode::RespawnPlayer(APlayerController* PlayerController)
{
	AActor* PlayerStart = FindPlayerStart(PlayerController);
	if (PlayerStart)
	{
		PlayerController->GetPawn()->SetActorLocation(PlayerStart->GetActorLocation());
	}
}

void ATopDownGameMode::ProjectileHit(ATopDownCharacter* HitTank, ATopDownCharacter* InstigatorTank)
{
	if (HitTank && InstigatorTank)
	{
		ATopDownPlayerController* HitTankController = HitTank->GetController<ATopDownPlayerController>();
		ATopDownPlayerController* TankOwnerController = InstigatorTank->GetController<ATopDownPlayerController>();
		if (HitTankController && TankOwnerController)
		{
			InstigatorTank->GetPlayerState<ATopDownPlayerState>()->IncreaseScore();
			RespawnPlayer(HitTankController);
		}
	}
}