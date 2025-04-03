// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/HUGameMode.h"
#include "GameState/HUGameState.h"

AHUGameMode::AHUGameMode()
{
	const ConstructorHelpers::FClassFinder<APawn> DefaultPawnRef(TEXT("/Game/Characters/BP_HUCharacterPlayer.BP_HUCharacterPlayer_C"));
	if (DefaultPawnRef.Class != nullptr)
	{
		DefaultPawnClass = DefaultPawnRef.Class;
	}

	TeamCount = 0;
}

int32 AHUGameMode::AddAndGetTeamCount()
{
	TeamCount++;
	return TeamCount;
}
