// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/HUGameState.h"

void AHUGameState::AddPlayerState(APlayerState* PlayerState)
{
	Super::AddPlayerState(PlayerState);

	OnPlayerArrAdded.Broadcast(PlayerState);
}

void AHUGameState::RemovePlayerState(APlayerState* PlayerState)
{
	Super::RemovePlayerState(PlayerState);

	OnPlayerArrRemoved.Broadcast(PlayerState);
}
