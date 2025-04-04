// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/HUAIController.h"

void AHUAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (HasAuthority())
	{
		RunAI();
	}
}

void AHUAIController::RunAI()
{
	if (HasAuthority())
	{
		if (BehaviorTreeAsset)
		{
			RunBehaviorTree(BehaviorTreeAsset);
		}
	}
}
