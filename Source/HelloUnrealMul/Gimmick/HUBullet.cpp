// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/HUBullet.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Interface/BulletHittableInterface.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AHUBullet::AHUBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = SphereComponent;

	// Collision Section
	SphereComponent->SetSphereRadius(50.f);
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AHUBullet::OnBulletOverlap);

	// Mesh Section
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	SphereMesh->SetupAttachment(SphereComponent);

	// Projectile Section
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 1000.f;
	ProjectileMovement->MaxSpeed = 1000.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	MaxTravelDistance = 50000.0f;

	bReplicates = true;
}

// Called when the game starts or when spawned
void AHUBullet::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SpawnLocation = GetActorLocation();
	}
}

// Called every frame
void AHUBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		float TravelDistance = FVector::Dist(SpawnLocation, GetActorLocation());
		if (TravelDistance >= MaxTravelDistance)
		{
			Destroy();
		}
	}
}

void AHUBullet::OnBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		IBulletHittableInterface* BulletHittableInterface = Cast<IBulletHittableInterface>(OtherActor);

		if (BulletHittableInterface != nullptr)
		{
			BulletHittableInterface->OnBulletHit(this, BulletOwner);
		}
	}
}

