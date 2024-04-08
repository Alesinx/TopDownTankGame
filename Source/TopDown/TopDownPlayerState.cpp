// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownPlayerState.h"

void ATopDownPlayerState::OnRep_Score()
{
	OnScoreUpdatedDelegate.Broadcast(GetScore());
}

int ATopDownPlayerState::IncreaseScore()
{
	float CurrentScore = GetScore();
	SetScore(CurrentScore + 1);

	return Score;
}
