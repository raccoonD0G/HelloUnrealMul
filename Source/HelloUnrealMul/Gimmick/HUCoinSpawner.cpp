// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/HUCoinSpawner.h"
#include "Gimmick/HUCoin.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Character/HUCharacterPlayer.h"
#include "PlayerState/HUPlayerState.h"
#include "Gimmick/HUBullet.h"

// Sets default values
AHUCoinSpawner::AHUCoinSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Collision Section
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;

	BoxComponent->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));

	// Mesh Section
	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));
	BoxMesh->SetupAttachment(BoxComponent);

	// Soin Spawn Section
	CoinCount = 0;

	bReplicates = true;
}

// Called when the game starts or when spawned
void AHUCoinSpawner::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AHUCoinSpawner::Server_Spawn, 5.0f, true);
	}
}

// Called every frame
void AHUCoinSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHUCoinSpawner::Server_Spawn_Implementation()
{
	if (HasAuthority())
	{
		if (CoinClass == nullptr)
		{
			return;
		}

		const FVector BaseLocation = GetActorLocation();
		const float SpawnRadius = 500.f;

		for (int32 i = 0; i < 10; ++i)
		{
			if (CoinCount < 10)
			{
				FVector2D RandPoint2D = FMath::RandPointInCircle(SpawnRadius);
				FVector RandomOffset = FVector(RandPoint2D.X, RandPoint2D.Y, 0.f);

				FVector SpawnLocation = BaseLocation + RandomOffset;
				FRotator SpawnRotation = FRotator::ZeroRotator;

				FActorSpawnParameters SpawnParams;
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

				AHUCoin* Coin = GetWorld()->SpawnActor<AHUCoin>(CoinClass, SpawnLocation, SpawnRotation, SpawnParams);
				if (Coin != nullptr)
				{
					CoinCount++;
					Coin->BindOnCoinCollected(this, &AHUCoinSpawner::Server_CoinCountDecrease);
				}
			}
			
		}
	}
}

void AHUCoinSpawner::Server_CoinCountDecrease_Implementation(AActor* CollectedActor)
{
	if (HasAuthority())
	{
		CoinCount--;
	}
}

void AHUCoinSpawner::OnBulletHit(AHUBullet* HitBullet, AActor* BulletOwner)
{
	if (HasAuthority())
	{
		HitBullet->Destroy();
	}

	AHUCharacterPlayer* Player = Cast<AHUCharacterPlayer>(BulletOwner);
	if (Player != nullptr)
	{
		AHUPlayerState* PlayerState = Cast<AHUPlayerState>(Player->GetPlayerState());
		if (PlayerState != nullptr)
		{
			PlayerState->MinusScoreOne();
		}
	}
}

