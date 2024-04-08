// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TopDownScoreWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class TOPDOWN_API UTopDownScoreWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Text block that holds a score string to be displayed to the player in the UI */
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ScoreTextBlock;

	virtual void NativeConstruct() override;

	/**
	 * Updates the text of the score TextBlock widget.
	 *
	 * @param ScoreValue - The new score value to be displayed.
	 */
	UFUNCTION(BlueprintCallable, Category = Score)
	virtual void SetScoreTextBlockText(int ScoreValue);

protected:
	/**
	 * Function bound to the ATopDownPlayerState::OnScoreUpdateDelegate.
	 *
	 * @param ScoreValue - The updated score value.
	 */
	UFUNCTION(BlueprintCallable, Category = Score)
	virtual void OnScoreUpdated(int ScoreValue);
};
