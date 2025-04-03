// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUHUD.generated.h"

/**
 * 
 */
UCLASS()
class HELLOUNREALMUL_API AHUHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UHUUserWidget> ScoreWidgetClass;

	UPROPERTY()
	TObjectPtr<class UHUUserWidget> ScoreWidget;
	
};
