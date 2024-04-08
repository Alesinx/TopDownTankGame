// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TopDownPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreUpdatedDelegate, int, ScoreValue);

/**
 * TopDown default player state. Handles score
 */
UCLASS()
class TOPDOWN_API ATopDownPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	/**
	* Get current score value
	*/
	UFUNCTION(BlueprintCallable, Category = "")
	int GetCurrentScore() { return Score; }

	/**
	 * Increase the current score.
	 *
	 * @param Amount The amount by which to increase the current score.
	 * @return The updated score after being increased by the specified amount.
	 */
	UFUNCTION(BlueprintCallable, Category = "Score")
	int IncreaseScore();

	UPROPERTY(BlueprintAssignable)
	FOnScoreUpdatedDelegate OnScoreUpdatedDelegate;

private:
	virtual void OnRep_Score() override;
};
