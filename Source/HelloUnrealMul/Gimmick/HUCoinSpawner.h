// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/BulletHittableInterface.h"
#include "HUCoinSpawner.generated.h"


UCLASS()
class HELLOUNREALMUL_API AHUCoinSpawner : public AActor, public IBulletHittableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHUCoinSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

// Collision Section
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UBoxComponent> BoxComponent;

// Mesh Section
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UStaticMeshComponent> BoxMesh;

// Coin Spawn Section
protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AHUCoin> CoinClass;

	UFUNCTION(Server, Reliable)
	void Server_Spawn();
	void Server_Spawn_Implementation();

	FTimerHandle SpawnTimerHandle;

	int32 CoinCount;

	UFUNCTION(Server, Reliable)
	void Server_CoinCountDecrease(AActor* CollectedActor);
	void Server_CoinCountDecrease_Implementation(AActor* CollectedActor);

// Bullet Section
protected:
	virtual void OnBulletHit(AHUBullet* HitBullet, AActor* BulletOwner) override;
};
