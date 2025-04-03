// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HUWallBase.generated.h"

UCLASS()
class HELLOUNREALMUL_API AHUWallBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHUWallBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

// Mesh Section
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UStaticMeshComponent> BoxMesh;

// Collision Section
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UBoxComponent> BoxComponent;

};
