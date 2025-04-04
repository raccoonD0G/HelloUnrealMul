// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_SetRandomPos.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"

EBTNodeResult::Type UBTTask_SetRandomPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (!ControlledPawn)
	{
		return EBTNodeResult::Failed;
	}

	FVector Origin = ControlledPawn->GetActorLocation();

	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	if (!NavSys)
	{
		return EBTNodeResult::Failed;
	}

	FNavLocation RandomLocation;

	uint8 bFound = NavSys->GetRandomPointInNavigableRadius(Origin, SearchRadius, RandomLocation);

	if (bFound)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(RandomPosKey.SelectedKeyName, RandomLocation.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

UBTTask_SetRandomPos::UBTTask_SetRandomPos()
{
	RandomPosKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_SetRandomPos, RandomPosKey));
}
