// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/HUGunComponent.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "PlayerController/HUPlayerController.h"
#include "Gimmick/HUBullet.h"


// Sets default values for this component's properties
UHUGunComponent::UHUGunComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHUGunComponent::BeginPlay()
{
	Super::BeginPlay();
	if (AActor* Owner = GetOwner())
	{
		if (APlayerController* PC = Cast<APlayerController>(Owner->GetInstigatorController()))
		{
			if (PC->IsLocalController())
			{
				if (ULocalPlayer* LocalPlayer = PC->GetLocalPlayer())
				{
					if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
					{
						if (GunInputMappingContext)
						{
							Subsystem->AddMappingContext(GunInputMappingContext, 1);
						}
					}
				}

				if (UEnhancedInputComponent* InputComp = Cast<UEnhancedInputComponent>(PC->InputComponent))
				{
					BindEnhancedInput(InputComp);
				}
			}
		}
	}
}



// Called every frame
void UHUGunComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHUGunComponent::BindEnhancedInput(UEnhancedInputComponent* InputComp)
{
	if (InputComp && FireAction)
	{
		InputComp->BindAction(FireAction, ETriggerEvent::Triggered, this, &UHUGunComponent::Server_SpawnBullet);
	}
}

void UHUGunComponent::Server_SpawnBullet_Implementation()
{
	if (!BulletClass) return;

	AActor* Owner = GetOwner();
	if (!Owner) return;

	if (!Owner->HasAuthority()) return;

	FVector SpawnLocation = GetComponentLocation();
	FRotator SpawnRotation = Owner->GetActorRotation();

	if (APlayerController* PC = Cast<APlayerController>(Owner->GetInstigatorController()))
	{
		FRotator ViewRot;
		FVector CameraLocation;
		PC->GetPlayerViewPoint(CameraLocation, ViewRot);
		SpawnRotation = ViewRot;
	}

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	Params.Instigator = Owner->GetInstigator();

	AHUBullet* Bullet = GetWorld()->SpawnActor<AHUBullet>(BulletClass, SpawnLocation, SpawnRotation, Params);
	Bullet->SetBulletOwner(GetOwner());
}

