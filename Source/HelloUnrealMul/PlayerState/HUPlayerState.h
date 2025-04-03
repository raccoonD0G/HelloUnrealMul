// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "HUPlayerState.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCurrentScoreChange, int32 /* TeamID */, int32 /* InScore */);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTeamIDChange, int32 /* InTeamID */);
/**
 * 
 */
UCLASS()
class HELLOUNREALMUL_API AHUPlayerState : public APlayerState
{
	GENERATED_BODY()

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

public:
	AHUPlayerState();

public:
	FORCEINLINE int32 GetCurrentScore() const { return CurrentScore; }
	FORCEINLINE int32 GetTeamID() const { return TeamID; }

	void PlusScoreOne();
	void MinusScoreOne();

	template<typename T>
	void BindOnScoreChange(T* InClass, void (T::*Func)(int32, int32))
	{
		OnCurrentScoreChange.Add(FOnCurrentScoreChange::FDelegate::CreateUObject(InClass, Func));
	}

	template<typename T>
	void BindOnTeamIDChange(T* InClass, void (T::*Func)(int32))
	{
		OnTeamIDChange.Add(FOnTeamIDChange::FDelegate::CreateUObject(InClass, Func));
	}

protected:
	UFUNCTION(Server, Reliable)
	void Server_PlusScoreOne();
	void Server_PlusScoreOne_Implementation();

	UFUNCTION(Server, Reliable)
	void Server_MinusScoreOne();
	void Server_MinusScoreOne_Implementation();

	UFUNCTION(Server, Reliable)
	void Server_SetScore(int32 InCurrentScore);
	void Server_SetScore_Implementation(int32 InCurrentScore);

	void SetScore(int32 InCurrentScore);

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_TeamID)
	int32 TeamID;

	UFUNCTION()
	void OnRep_TeamID();

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_CurrentScore)
	int32 CurrentScore;

    UFUNCTION()
    void OnRep_CurrentScore();

	FOnTeamIDChange OnTeamIDChange;
	FOnCurrentScoreChange OnCurrentScoreChange;

public:
	FORCEINLINE void SetTeamID(int32 InTeamID) { TeamID = InTeamID; }
};
