// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "HUAIController.generated.h"

/**
 * 
 */
UCLASS()
class HELLOUNREALMUL_API AHUAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	virtual void OnPossess(APawn* InPawn) override;

// AI Section
protected:
	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<class UBehaviorTree> BehaviorTreeAsset;

public:
	FORCEINLINE class UBehaviorTree* GetBehaviorTreeAsset() const { return BehaviorTreeAsset; }

	void RunAI();

};
