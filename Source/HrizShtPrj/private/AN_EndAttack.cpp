// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_EndAttack.h"
#include "BossAnimInstance.h"

void UAN_EndAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp)
	{
		UBossAnimInstance* bossEnemyIns = Cast<UBossAnimInstance>(MeshComp->GetAnimInstance());

		if (bossEnemyIns != nullptr)
		{
			bossEnemyIns->isAttaking = false;
			bossEnemyIns->animLength = 0;

			bossEnemyIns->BeforePattern = bossEnemyIns->patternNum;
			
			bossEnemyIns->patternNum = -1;
		}
	}
}
