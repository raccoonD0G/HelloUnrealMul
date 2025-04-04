// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_DetectPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "Character/HUCharacterPlayer.h"
#include "Interface/PlayerDetectableInterface.h"

UBTService_DetectPlayer::UBTService_DetectPlayer()
{
	NodeName = TEXT("Detect Player");
	PlayerKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_DetectPlayer, PlayerKey), AHUCharacterPlayer::StaticClass());

	Interval = 0.5f;
}

void UBTService_DetectPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
    APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
    if (!ControlledPawn)
    {
        return;
    }

    UWorld* World = ControlledPawn->GetWorld();
    if (!World)
    {
        return;
    }
    FVector Origin = ControlledPawn->GetActorLocation();

    TArray<FOverlapResult> OverlapResults;
    FCollisionQueryParams QueryParams(SCENE_QUERY_STAT(DetectPlayer), false, ControlledPawn);

    bool bHit = World->OverlapMultiByObjectType(
        OverlapResults,
        Origin,
        FQuat::Identity,
        FCollisionObjectQueryParams(ECollisionChannel::ECC_Pawn),
        FCollisionShape::MakeSphere(DetectRadius),
        QueryParams
    );

    AHUCharacterPlayer* NearestPlayer = nullptr;
    float NearestDistSqr = DetectRadius * DetectRadius;

    for (const FOverlapResult& Result : OverlapResults)
    {
        AHUCharacterPlayer* Player = Cast<AHUCharacterPlayer>(Result.GetActor());
        if (Player && IsValid(Player))
        {
            float DistSqr = FVector::DistSquared(Player->GetActorLocation(), Origin);
            if (DistSqr < NearestDistSqr)
            {
                NearestPlayer = Player;
                NearestDistSqr = DistSqr;
            }
        }
    }

    UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
    if (NearestPlayer)
    {
        BB->SetValueAsObject(PlayerKey.SelectedKeyName, NearestPlayer);

        IPlayerDetectableInterface* PlayerDetectableInterface = Cast<IPlayerDetectableInterface>(OwnerComp.GetAIOwner());
        if (PlayerDetectableInterface != nullptr)
        {
            PlayerDetectableInterface->OnPlayerDetected();
        }
    }
    else
    {
        BB->ClearValue(PlayerKey.SelectedKeyName);

        IPlayerDetectableInterface* PlayerDetectableInterface = Cast<IPlayerDetectableInterface>(OwnerComp.GetAIOwner());
        if (PlayerDetectableInterface != nullptr)
        {
            PlayerDetectableInterface->OnPlayerNotDetected();
        }
    }
}
