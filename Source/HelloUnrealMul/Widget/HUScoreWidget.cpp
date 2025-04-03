// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/HUScoreWidget.h"
#include "Components/TextBlock.h"
#include "PlayerState/HUPlayerState.h"
#include "GameState/HUGameState.h"

void UHUScoreWidget::NativeConstruct()
{
	Super::NativeConstruct();
	InitScoreWidget();
}

void UHUScoreWidget::UpdateScore(int32 InTeamID, int32 InScore)
{
	if (TeamNameScores.Contains(InTeamID))
	{
		TeamNameScores[InTeamID] = InScore;
	}

	SetScoreText();
}

void UHUScoreWidget::PlayerStateAdded(APlayerState* AddedPlayerState)
{
	AHUPlayerState* HUPlayerState = Cast<AHUPlayerState>(AddedPlayerState);
	if (HUPlayerState != nullptr)
	{
		if (TeamNameScores.Contains(HUPlayerState->GetTeamID()))
		{
			TeamNameScores[HUPlayerState->GetTeamID()] = HUPlayerState->GetCurrentScore();
		}
		else
		{
			TeamNameScores.Add(HUPlayerState->GetTeamID(), HUPlayerState->GetCurrentScore());
		}
	}

	SetScoreText();
}

void UHUScoreWidget::PlayerStateRemoved(APlayerState* RemovedPlayerState)
{
	AHUPlayerState* HUPlayerState = Cast<AHUPlayerState>(RemovedPlayerState);
	if (HUPlayerState != nullptr)
	{
		if (TeamNameScores.Contains(HUPlayerState->GetTeamID()))
		{
			TeamNameScores.Remove(HUPlayerState->GetTeamID());
		}
	}

	SetScoreText();
}

void UHUScoreWidget::InitScoreWidget()
{
	GetWorld()->GetTimerManager().SetTimer(InitWithGameStateTimerHandle, this, &UHUScoreWidget::InitWithGameState, 0.1f, false);
	GetWorld()->GetTimerManager().SetTimer(InitWithPlayerStateTimerHandle, this, &UHUScoreWidget::InitWithPlayerState, 0.1f, false);
}

void UHUScoreWidget::InitWithGameState()
{
	UWorld* World = GetWorld();

	if (World != nullptr)
	{
		AGameStateBase* GameState = World->GetGameState();

		if (GameState != nullptr)
		{
			AHUGameState* HUGameState = Cast<AHUGameState>(GameState);
			if (HUGameState != nullptr)
			{
				HUGameState->BindOnPlayerArrAdded(this, &UHUScoreWidget::PlayerStateAdded);
				HUGameState->BindOnPlayerArrRemoved(this, &UHUScoreWidget::PlayerStateRemoved);
				return;
			}
		}
	}

	GetWorld()->GetTimerManager().ClearTimer(InitWithGameStateTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(InitWithGameStateTimerHandle, this, &UHUScoreWidget::InitWithGameState, 0.1f, false);
}

void UHUScoreWidget::InitWithPlayerState()
{
	UWorld* World = GetWorld();

	if (World != nullptr)
	{
		AGameStateBase* GameState = World->GetGameState();

		if (GameState != nullptr)
		{
			TArray<APlayerState*>& PlayerStates = GameState->PlayerArray;
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("%d"), PlayerStates.Num()));
			for (const auto& PlayerState : PlayerStates)
			{
				AHUPlayerState* HUPlayerState = Cast<AHUPlayerState>(PlayerState);
				if (HUPlayerState != nullptr)
				{
					HUPlayerState->BindOnScoreChange(this, &UHUScoreWidget::UpdateScore);
					HUPlayerState->BindOnTeamIDChange(this, &UHUScoreWidget::ResetTeamNameScoresB);
					HUPlayerState->BindOnPlayerStateInit(this, &UHUScoreWidget::ResetTeamNameScoresA);
					TeamNameScores.Add(HUPlayerState->GetTeamID(), HUPlayerState->GetCurrentScore());
				}
			}
			SetScoreText();
			return;
		}
	}

	GetWorld()->GetTimerManager().ClearTimer(InitWithPlayerStateTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(InitWithPlayerStateTimerHandle, this, &UHUScoreWidget::InitWithPlayerState, 0.1f, false);
}

void UHUScoreWidget::ResetTeamNameScoresA()
{
	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		AGameStateBase* GameState = World->GetGameState();

		if (GameState != nullptr)
		{
			TArray<APlayerState*>& PlayerStates = GameState->PlayerArray;
			TeamNameScores.Empty();
			for (const auto& PlayerState : PlayerStates)
			{
				AHUPlayerState* HUPlayerState = Cast<AHUPlayerState>(PlayerState);
				if (HUPlayerState != nullptr)
				{
					TeamNameScores.Add(HUPlayerState->GetTeamID(), HUPlayerState->GetCurrentScore());
				}
			}
			SetScoreText();
		}
	}
}

void UHUScoreWidget::ResetTeamNameScoresB(int32 TeamID)
{
	ResetTeamNameScoresA();
}

void UHUScoreWidget::SetScoreText()
{
	FString ScoresStr = FString();

	for (const auto& TeamNameScore : TeamNameScores)
	{
		ScoresStr.Append(FString::Printf(TEXT("Team %d : %d\n"), TeamNameScore.Key, TeamNameScore.Value));
	}

	ScoreText->SetText(FText::FromString(ScoresStr));
}

