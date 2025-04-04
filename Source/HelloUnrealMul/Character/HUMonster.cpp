// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HUMonster.h"

AHUMonster::AHUMonster()
{
	bReplicates = true;
}

void AHUMonster::Multicast_PlayAttackMontage_Implementation()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && AttackMontage && !AnimInstance->Montage_IsPlaying(AttackMontage))
	{
		AnimInstance->Montage_Play(AttackMontage);
	}
}

bool AHUMonster::IsAttackMontageEnded() const
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (!AnimInstance || !AttackMontage) return true;

	return !AnimInstance->Montage_IsPlaying(AttackMontage);
}
