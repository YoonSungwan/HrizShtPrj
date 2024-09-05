// Fill out your copyright notice in the Description page of Project Settings.


#include "ANS_BakcAndRush.h"
#include "BossAnimInstance.h"

void UANS_BakcAndRush::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (MeshComp)
	{
		bossEnemyIns = Cast<UBossAnimInstance>(MeshComp->GetAnimInstance());

		if (bossEnemyIns != nullptr)
		{
			initLoc = bossEnemyIns->owingPawnLoc;
			backLoc = FVector(initLoc.X, initLoc.Y + stepBack, initLoc.Z);
			bossSpd = bossEnemyIns->moveSpd;

			bossEnemy = bossEnemyIns->GetOwningActor();
		}
	}
}

void UANS_BakcAndRush::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	if (MeshComp && bossEnemy != nullptr)
	{
		bossEnemy->SetActorLocation(bossEnemy->GetActorLocation() + (-(bossEnemy->GetActorRightVector()) * (3400.00) * FrameDeltaTime));
	}
}

void UANS_BakcAndRush::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp)
	{
		if (bossEnemyIns != nullptr)
		{
			bossEnemyIns->isAttaking = false;
			bossEnemyIns->animLength = 0;

			bossEnemyIns->BeforePattern = bossEnemyIns->patternNum;
			
			bossEnemyIns->patternNum = 3;
		}
	}
}
