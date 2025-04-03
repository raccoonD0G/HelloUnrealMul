// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HUBullet.generated.h"

UCLASS()
class HELLOUNREALMUL_API AHUBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHUBullet();

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

	UFUNCTION()
	void OnBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

// Mesh Section
protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<class UStaticMeshComponent> SphereMesh;

// Projectile Section
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<class UProjectileMovementComponent> ProjectileMovement;

	float MaxTravelDistance;
	FVector SpawnLocation;

// Owner Section
protected:
	UPROPERTY()
	TObjectPtr<AActor> BulletOwner;

public:
	FORCEINLINE void SetBulletOwner(AActor* InBulletOwner) { BulletOwner = InBulletOwner; }
};
