// Fill out your copyright notice in the Description page of Project Settings.


#include "ANS_Rush.h"
#include "BossAnimInstance.h"

void UANS_Rush::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (MeshComp)
	{
		bossEnemyIns = Cast<UBossAnimInstance>(MeshComp->GetAnimInstance());
		bossEnemy = MeshComp->GetOwner();
	}
}

void UANS_Rush::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	if (MeshComp && bossEnemy != nullptr)
	{
		FVector bossLoc = bossEnemy->GetActorLocation();
		bossEnemy->SetActorLocation(bossLoc + (bossEnemy->GetActorRightVector()) * (3000.00) * FrameDeltaTime);
	}
}

void UANS_Rush::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp)
	{
		if (bossEnemyIns != nullptr)
		{
			bossEnemy->SetActorLocation(bossEnemyIns->enemyInitLoc);

			bossEnemyIns->isAttaking = false;
			bossEnemyIns->animLength = 0;

			bossEnemyIns->BeforePattern = bossEnemyIns->patternNum;
			
			bossEnemyIns->patternNum = -1;
		}
	}
}
