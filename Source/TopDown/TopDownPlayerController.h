// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "TopDownPlayerController.generated.h"

/** Forward declaration */
class UInputAction;
class UInputMappingContext;
class UNiagaraSystem;
class UTopDownScoreWidget;
class UPathFollowingComponent;

UCLASS()
class ATopDownPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATopDownPlayerController();

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	/** Set destination click input action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SetDestinationClickAction;

	/** Fire tank input action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* FireTankAction;

	/** The instantiate score widget*/
	UPROPERTY(BlueprintReadOnly, Category = "Score")
	UTopDownScoreWidget* ScoreWidget;

	/* Path following component used for navigation */
	UPROPERTY(BlueprintReadOnly, Category = "Navigation")
	UPathFollowingComponent* PathFollowingComp;

protected:
	/** Score widget class what will be instantiated int the begin play */
	UPROPERTY(EditAnywhere, Category = "Score")
	TSubclassOf<UTopDownScoreWidget> ScoreWidgetClass;

	/** Sets a goal location for the tank to navigate to */
	UFUNCTION(BlueprintCallable, Category = "Tank controller")
	void MoveTankToLocation(const FVector& GoalLocation);

	virtual void SetupInputComponent() override;
	virtual void BeginPlayingState() override;
	virtual void OnSetDestinationTriggered();
	virtual void OnSetDestinationReleased();
	virtual void OnFireInputStarted();

private: 
	FVector CachedGoalLocation;
	bool WasHitSusccessful = false;
};


