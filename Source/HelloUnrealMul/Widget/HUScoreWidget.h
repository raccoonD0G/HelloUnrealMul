// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/HUUserWidget.h"
#include "HUScoreWidget.generated.h"

/**
 * 
 */
UCLASS()
class HELLOUNREALMUL_API UHUScoreWidget : public UHUUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> ScoreText;
	
public:
	void UpdateScore(int32 InTeamID, int32 InScore);

	void PlayerStateAdded(APlayerState* AddedPlayerState);
	void PlayerStateRemoved(APlayerState* RemovedPlayerState);

protected:
	UPROPERTY()
	TMap<int32 /* TeamID */, int32 /* Score */> TeamNameScores;

	UFUNCTION()
	void InitScoreWidget();

	UFUNCTION()
	void InitWithGameState();

	UFUNCTION()
	void InitWithPlayerState();

protected:
	void ResetTeamNameScores();

	void ResetTeamNameScores(int32 InTeamID);

	FTimerHandle InitWithPlayerStateTimerHandle;
	FTimerHandle InitWithGameStateTimerHandle;

protected:
	void SetScoreText();
};
