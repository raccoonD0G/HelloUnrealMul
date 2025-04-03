// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gimmick/HUWallBase.h"
#include "Interface/BulletHittableInterface.h"
#include "HUBulletProofWall.generated.h"

/**
 * 
 */
UCLASS()
class HELLOUNREALMUL_API AHUBulletProofWall : public AHUWallBase, public IBulletHittableInterface
{
	GENERATED_BODY()
	
public:
	AHUBulletProofWall();
	
// Bullet Section
public:
	virtual void OnBulletHit(AHUBullet* HitBullet, AActor* BulletOwner) override;
};
