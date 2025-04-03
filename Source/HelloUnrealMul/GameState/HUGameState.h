// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "HUGameState.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerArrAdded, APlayerState* /* AddedPlayerState */);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerArrRemoved, APlayerState* /* RemovedPlayerState */);
/**
 * 
 */
UCLASS()
class HELLOUNREALMUL_API AHUGameState : public AGameStateBase
{
	GENERATED_BODY()

// Add Player State Section
protected:
	virtual void AddPlayerState(APlayerState* PlayerState) override;
	virtual void RemovePlayerState(APlayerState* PlayerState) override;

	FOnPlayerArrAdded OnPlayerArrAdded;
	FOnPlayerArrRemoved OnPlayerArrRemoved;

public:
	template<typename T>
	void BindOnPlayerArrAdded(T* InClass, void (T::*Func)(APlayerState*))
	{
		OnPlayerArrAdded.Add(FOnPlayerArrAdded::FDelegate::CreateUObject(InClass, Func));
	}

	template<typename T>
	void BindOnPlayerArrRemoved(T* InClass, void (T::*Func)(APlayerState*))
	{
		OnPlayerArrRemoved.Add(FOnPlayerArrRemoved::FDelegate::CreateUObject(InClass, Func));
	}

};
