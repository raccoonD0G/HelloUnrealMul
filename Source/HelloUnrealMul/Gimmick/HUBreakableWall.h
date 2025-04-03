// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gimmick/HUWallBase.h"
#include "Interface/BulletHittableInterface.h"
#include "HUBreakableWall.generated.h"

/**
 * 
 */
UCLASS()
class HELLOUNREALMUL_API AHUBreakableWall : public AHUWallBase, public IBulletHittableInterface
{
	GENERATED_BODY()
	
public:
	AHUBreakableWall();

// Bullet Section
public:
	virtual void OnBulletHit(AHUBullet* HitBullet, AActor* BulletOwner) override;
};
