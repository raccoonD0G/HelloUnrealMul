// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SetRandomPos.generated.h"

/**
 * 
 */
UCLASS()
class HELLOUNREALMUL_API UBTTask_SetRandomPos : public UBTTaskNode
{
	GENERATED_BODY()
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UBTTask_SetRandomPos();

public:
	UPROPERTY(EditAnywhere, Category = "AI")
	float SearchRadius = 1000.0f;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector RandomPosKey;
};
