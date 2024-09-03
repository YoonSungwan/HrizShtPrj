// Fill out your copyright notice in the Description page of Project Settings.


#include "BossAnimInstance.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

void UBossAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	player = UGameplayStatics::GetPlayerCharacter(this, 0);
}

void UBossAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}
