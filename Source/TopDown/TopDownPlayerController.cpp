// Copyright Epic Games, Inc. All Rights Reserved.

#include "TopDownPlayerController.h"
#include "GameFramework/Pawn.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "TopDownCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "TopDownGameMode.h"
#include "TopDownScoreWidget.h"
#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"

ATopDownPlayerController::ATopDownPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedGoalLocation = FVector::ZeroVector;
}

void ATopDownPlayerController::BeginPlayingState()
{
	Super::BeginPlayingState();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	if (IsLocalController())
	{
		if (ScoreWidgetClass)
		{
			ScoreWidget = CreateWidget<UTopDownScoreWidget>(this, ScoreWidgetClass);
			if (ScoreWidget)
			{
				ScoreWidget->AddToViewport();
			}
		}
	}

	PathFollowingComp = this->FindComponentByClass<UPathFollowingComponent>();
	if (PathFollowingComp == nullptr)
	{
		PathFollowingComp = NewObject<UPathFollowingComponent>(this);
		PathFollowingComp->RegisterComponentWithWorld(GetWorld());
		PathFollowingComp->Initialize();
	}
}

void ATopDownPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &ATopDownPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &ATopDownPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(FireTankAction, ETriggerEvent::Started, this, &ATopDownPlayerController::OnFireInputStarted);
	}
}

void ATopDownPlayerController::MoveTankToLocation(const FVector& GoalLocation)
{

	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this->GetWorld());
	if (NavSys == nullptr)
	{
		return;
	}

	if (PathFollowingComp == nullptr)
	{
		return;
	}

	if (!PathFollowingComp->IsPathFollowingAllowed())
	{
		return;
	}

	const FVector AgentNavLocation = this->GetNavAgentLocation();
	const FNavAgentProperties Properties = this->GetNavAgentPropertiesRef();
	const ANavigationData* NavData = NavSys->GetNavDataForProps(Properties, AgentNavLocation);
	if (NavData)
	{
		FPathFindingQuery Query(this, *NavData, AgentNavLocation, GoalLocation);
		FPathFindingResult Result = NavSys->FindPathSync(Query);
		FAIMoveRequest RequetData = FAIMoveRequest(GoalLocation);
		RequetData.SetAcceptanceRadius(0.01f);
		if (Result.IsSuccessful())
		{
			PathFollowingComp->RequestMove(RequetData, Result.Path);
		}
	}
}

void ATopDownPlayerController::OnSetDestinationTriggered()
{
	FHitResult Hit;
	WasHitSusccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	if (WasHitSusccessful)
	{
		MoveTankToLocation(Hit.Location);
		CachedGoalLocation = Hit.Location;
	}
}

void ATopDownPlayerController::OnSetDestinationReleased()
{
	if (WasHitSusccessful)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedGoalLocation, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}
}

void ATopDownPlayerController::OnFireInputStarted()
{
	ATopDownCharacter* Tank = GetPawn<ATopDownCharacter>();
	if (Tank)
	{
		Tank->FireTank();
	}
}
