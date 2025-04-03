// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HUCharacterBase.h"

// Sets default values
AHUCharacterBase::AHUCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHUCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHUCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHUCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

