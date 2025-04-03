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
	
public:
	AHUGameMode();

// Team Section
protected:
	int32 TeamCount;

public:
	int32 AddAndGetTeamCount();


	
};
