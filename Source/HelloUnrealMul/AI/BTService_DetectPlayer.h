// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_DetectPlayer.generated.h"

/**
 * 
 */
UCLASS()
class HELLOUNREALMUL_API UBTService_DetectPlayer : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_DetectPlayer();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:
	UPROPERTY(EditAnywhere, Category = "AI")
	float DetectRadius = 500.0f;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector PlayerKey;
};
