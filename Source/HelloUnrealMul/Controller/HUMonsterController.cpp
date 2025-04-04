// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/HUMonsterController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Animation/AnimInstance.h"
#include "Character/HUMonster.h"

AHUMonsterController::AHUMonsterController()
{
}

void AHUMonsterController::SetCurrentState(EMonsterState NewMonsterState)
{
	UBlackboardComponent* BlackboardComp = GetBlackboardComponent();
	
	if (BlackboardComp == nullptr) return;

	switch (NewMonsterState)
	{
	case EMonsterState::Patrol:
		BlackboardComp->SetValueAsEnum(TEXT("MonsterState"), static_cast<uint8>(EMonsterState::Patrol));
		break;
	case EMonsterState::Chase:
		BlackboardComp->SetValueAsEnum(TEXT("MonsterState"), static_cast<uint8>(EMonsterState::Chase));
		break;
	case EMonsterState::Battle:
		BlackboardComp->SetValueAsEnum(TEXT("MonsterState"), static_cast<uint8>(EMonsterState::Battle));
		break;
	default:
		break;
	}

	CurrentState = NewMonsterState;
}

void AHUMonsterController::OnPlayerDetected()
{
	if (HasAuthority())
	{
		UBlackboardComponent* BlackboardComp = GetBlackboardComponent();
		AActor* Player = Cast<AActor>(BlackboardComp->GetValueAsObject(TEXT("Player")));
		float DistToPlayer = (Player->GetActorLocation() - GetPawn()->GetActorLocation()).Length();
		if (DistToPlayer < 100.0f)
		{
			SetCurrentState(EMonsterState::Battle);
		}
		else
		{
			SetCurrentState(EMonsterState::Chase);
		}
	}
}

void AHUMonsterController::OnPlayerNotDetected()
{
	SetCurrentState(EMonsterState::Patrol);
}

void AHUMonsterController::StartAttack()
{
	if (HasAuthority())
	{
		AHUMonster* Monster = Cast<AHUMonster>(GetPawn());
		if (Monster)
		{
			Monster->Multicast_PlayAttackMontage();
		}
	}
}

bool AHUMonsterController::IsAttackEnd()
{
	AHUMonster* Monster = Cast<AHUMonster>(GetPawn());
	if (!Monster) return true;

	return Monster->IsAttackMontageEnded();
}

void AHUMonsterController::EndAttack()
{
	SetCurrentState(EMonsterState::Chase);
}
