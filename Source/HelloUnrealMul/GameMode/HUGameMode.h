// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HUGameMode.generated.h"

/**
 * 
 */
UCLASS()
class HELLOUNREALMUL_API AHUGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	virtual void PostLogin(APlayerController* NewPlayer) override;

	
public:
	AHUGameMode();

// Team Section
protected:
	int32 TeamCount;

public:
	int32 AddAndGetTeamCount();


	
};
