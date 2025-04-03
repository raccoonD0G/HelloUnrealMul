// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/BulletHittableInterface.h"
#include "HUCoin.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnCoinCollected, AActor* /* CollectedActor */)

UCLASS()
class HELLOUNREALMUL_API AHUCoin : public AActor, public IBulletHittableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHUCoin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


// Collision Section
protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<class USphereComponent> SphereComponent;

	void DestorySelf();

// Mesh Section
protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<class UStaticMeshComponent> SphereMesh;

// Collectible Section
public:
	template<typename T>
	void BindOnCoinCollected(T* InInstance, void (T::* InFunc)(AActor*))
	{
		OnCoinCollected.Add(FOnCoinCollected::FDelegate::CreateUObject(InInstance, InFunc));
	}

protected:
	FOnCoinCollected OnCoinCollected;

// Bullet Section
public:
	virtual void OnBulletHit(AHUBullet* HitBullet, AActor* BulletOwner) override;
};
