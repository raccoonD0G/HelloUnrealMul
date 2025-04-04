// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Controller/HUAIController.h"
#include "Interface/PlayerDetectableInterface.h"
#include "Interface/AttackableInterface.h"
#include "HUMonsterController.generated.h"

UENUM(BlueprintType)
enum class EMonsterState : uint8
{
	Patrol,
	Chase,
	Battle
};

/**
 * 
 */
UCLASS()
class HELLOUNREALMUL_API AHUMonsterController : public AHUAIController, public IPlayerDetectableInterface, public IAttackableInterface
{
	GENERATED_BODY()
	
public:
	AHUMonsterController();

// State Section
private:
	EMonsterState CurrentState;

protected:
	FORCEINLINE EMonsterState GetCurrentState() const { return CurrentState; }

	void SetCurrentState(EMonsterState NewMonsterState);

// Player Detect Section
public:
	virtual void OnPlayerDetected() override;
	virtual void OnPlayerNotDetected() override;

// Attack Section
public:
	virtual void StartAttack() override;
	virtual bool IsAttackEnd() override;
	virtual void EndAttack() override;
};
