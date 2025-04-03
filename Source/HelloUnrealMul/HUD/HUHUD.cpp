// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/HUHUD.h"
#include "Widget/HUUserWidget.h"

void AHUHUD::BeginPlay()
{
	Super::BeginPlay();

	if (ScoreWidgetClass)
	{
		ScoreWidget = CreateWidget<UHUUserWidget>(GetWorld(), ScoreWidgetClass);
		if (ScoreWidget)
		{
			ScoreWidget->AddToViewport();
		}
	}

}
