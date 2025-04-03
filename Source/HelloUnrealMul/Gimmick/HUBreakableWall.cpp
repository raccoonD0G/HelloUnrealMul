// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/HUBreakableWall.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Gimmick/HUBullet.h"

AHUBreakableWall::AHUBreakableWall()
{
	// Collision Section
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;

	// Mesh Section
	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));
	BoxMesh->SetupAttachment(BoxComponent);

	bReplicates = true;
}

void AHUBreakableWall::OnBulletHit(AHUBullet* HitBullet, AActor* BulletOwner)
{
	if (HasAuthority())
	{
		this->Destroy();
	}
}
