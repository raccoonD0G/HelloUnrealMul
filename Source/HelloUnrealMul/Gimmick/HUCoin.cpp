// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/HUCoin.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Character/HUCharacterPlayer.h"
#include "PlayerState/HUPlayerState.h"
#include "Gimmick/HUBullet.h"


// Sets default values
AHUCoin::AHUCoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = SphereComponent;

	// Sphere Section
	SphereComponent->SetSphereRadius(50.f);

	// Mesh Section
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	SphereMesh->SetupAttachment(SphereComponent);

	// Physics Section
	SphereComponent->SetSimulatePhysics(true);

	bReplicates = true;
}

// Called when the game starts or when spawned
void AHUCoin::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHUCoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHUCoin::DestorySelf()
{
	if (GetValid(this))
	{
		Destroy();
	}
}

void AHUCoin::OnBulletHit(AHUBullet* HitBullet, AActor* BulletOwner)
{
	OnCoinCollected.Broadcast(BulletOwner);

	if (HasAuthority())
	{
		HitBullet->Destroy();
		DestorySelf();
	}

	AHUCharacterPlayer* Player = Cast<AHUCharacterPlayer>(BulletOwner);
	if (Player != nullptr)
	{
		AHUPlayerState* PlayerState = Cast<AHUPlayerState>(Player->GetPlayerState());
		if (PlayerState != nullptr)
		{
			PlayerState->PlusScoreOne();
		}
	}
}
