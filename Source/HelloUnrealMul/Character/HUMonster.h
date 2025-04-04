// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/HUCharacterNonPlayer.h"
#include "HUMonster.generated.h"

/**
 * 
 */
UCLASS()
class HELLOUNREALMUL_API AHUMonster : public AHUCharacterNonPlayer
{
	GENERATED_BODY()
	
public:
	AHUMonster();

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_PlayAttackMontage();
	void Multicast_PlayAttackMontage_Implementation();

	UFUNCTION(BlueprintCallable)
	bool IsAttackMontageEnded() const;

protected:
	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* AttackMontage;
};
