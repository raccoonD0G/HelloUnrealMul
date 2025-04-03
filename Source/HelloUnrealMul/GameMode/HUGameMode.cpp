// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/HUGameMode.h"
#include "GameState/HUGameState.h"
#include "PlayerState/HUPlayerState.h"

APlayerController* AHUGameMode::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	APlayerController* Controller = Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);
	return Controller;
}

void AHUGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	AHUPlayerState* HUPlayerState = Cast<AHUPlayerState>(NewPlayer->PlayerState);
	HUPlayerState->SetTeamID(AddAndGetTeamCount());
}

AHUGameMode::AHUGameMode()
{
	const ConstructorHelpers::FClassFinder<APawn> DefaultPawnRef(TEXT("/Game/Characters/BP_HUCharacterPlayer.BP_HUCharacterPlayer_C"));
	if (DefaultPawnRef.Class != nullptr)
	{
		DefaultPawnClass = DefaultPawnRef.Class;
	}
}

int32 AHUGameMode::AddAndGetTeamCount()
{
	TeamCount++;
	return TeamCount;
}
