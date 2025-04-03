// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "HUGunComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HELLOUNREALMUL_API UHUGunComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHUGunComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

// Input Section
protected:
	void BindEnhancedInput(class UEnhancedInputComponent* InputComp);

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UInputAction> FireAction;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UInputMappingContext> GunInputMappingContext;

// Fire Section
protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AHUBullet> BulletClass;

	UFUNCTION(Server, reliable)
	void Server_SpawnBullet();
	void Server_SpawnBullet_Implementation();
};
