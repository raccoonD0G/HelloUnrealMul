// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Attack.h"
#include "Interface/AttackableInterface.h"
#include "Controller/HUAIController.h"

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    IAttackableInterface* AttackableInterface = Cast<IAttackableInterface>(OwnerComp.GetAIOwner());
    if (AttackableInterface != nullptr)
    {
        AttackableInterface->StartAttack();
    }

    return EBTNodeResult::InProgress;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    IAttackableInterface* AttackableInterface = Cast<IAttackableInterface>(OwnerComp.GetAIOwner());
    
    if (AttackableInterface == nullptr)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    if (AttackableInterface->IsAttackEnd())
    {
        AttackableInterface->EndAttack();
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }
}

UBTTask_Attack::UBTTask_Attack()
{
    NodeName = TEXT("Attack");
    bNotifyTick = true;
}
