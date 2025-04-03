// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerState/HUPlayerState.h"
#include "Net/UnrealNetwork.h"

void AHUPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AHUPlayerState, CurrentScore);
	DOREPLIFETIME(AHUPlayerState, TeamID);
}

void AHUPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (HasAuthority())
	{
		Server_SetScore(0);
	}
}

void AHUPlayerState::BeginPlay()
{
	Super::BeginPlay();
}



AHUPlayerState::AHUPlayerState()
{
	CurrentScore = 0;
	TeamID = 0;
}

void AHUPlayerState::PlusScoreOne()
{
	SetScore(CurrentScore + 1);
}

void AHUPlayerState::MinusScoreOne()
{
	SetScore(CurrentScore - 1);
}

void AHUPlayerState::Server_PlusScoreOne_Implementation()
{
	Server_SetScore(CurrentScore + 1);
}

void AHUPlayerState::Server_MinusScoreOne_Implementation()
{
	Server_SetScore(CurrentScore - 1);
}

void AHUPlayerState::Server_SetScore_Implementation(int32 InCurrentScore)
{
	CurrentScore = InCurrentScore;
	OnCurrentScoreChange.Broadcast(TeamID, InCurrentScore);
}

void AHUPlayerState::SetScore(int32 InCurrentScore)
{
	CurrentScore = InCurrentScore;
	OnCurrentScoreChange.Broadcast(TeamID, InCurrentScore);
	Server_SetScore(InCurrentScore);
}

void AHUPlayerState::OnRep_TeamID()
{
	OnTeamIDChange.Broadcast(TeamID);
}

void AHUPlayerState::OnRep_CurrentScore()
{
	OnCurrentScoreChange.Broadcast(TeamID, CurrentScore);
}
