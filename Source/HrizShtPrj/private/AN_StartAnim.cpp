// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_StartAnim.h"
#include "BossAnimInstance.h"

void UAN_StartAnim::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (Animation)
	{
		UBossAnimInstance* bossEnemyIns = Cast<UBossAnimInstance>(MeshComp->GetAnimInstance());

		if (bossEnemyIns != nullptr)
		{
			//bossEnemyIns->isAttaking = true;

			float putLength = Animation->GetPlayLength();

			bossEnemyIns->animLength = putLength;
		}
	}

}
