// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownScoreWidget.h"
#include "Components/TextBlock.h"
#include "TopDownPlayerState.h"

void UTopDownScoreWidget::NativeConstruct()
{
    Super::NativeConstruct();

    auto Controller = GetOwningPlayer();
    if (Controller->IsLocalController())
    {
        ATopDownPlayerState* TDPlayerState = Cast<ATopDownPlayerState>(Controller->PlayerState);
        if (TDPlayerState)
        {
            SetScoreTextBlockText(TDPlayerState->GetCurrentScore());
            TDPlayerState->OnScoreUpdatedDelegate.AddDynamic(this, &UTopDownScoreWidget::OnScoreUpdated);
        }
    }
}

void UTopDownScoreWidget::OnScoreUpdated(int ScoreValue)
{
    SetScoreTextBlockText(ScoreValue);
}

void UTopDownScoreWidget::SetScoreTextBlockText(int ScoreValue)
{
    if (ScoreTextBlock)
    {
        FString ScoreText = FString::Printf(TEXT("Your score: %d"), ScoreValue);
        FText FormattedScoreText = FText::FromString(ScoreText);
        ScoreTextBlock->SetText(FormattedScoreText);
    }
}
