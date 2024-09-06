// Fill out your copyright notice in the Description page of Project Settings.


#include "ANS_BossBullet.h"
#include "BossAnimInstance.h"

void UANS_BossBullet::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	
	if(MeshComp->GetOwner())
	{
		UBossAnimInstance* bossEnemyIns = Cast<UBossAnimInstance>(MeshComp->GetAnimInstance());

		if(!IsValid(bossEnemyIns))
		{
			return;
		}
		
		if(!(Animation->GetName().Contains("Armature_Attack_03_full")))
		{
			bossEnemyIns->FallBullet();	
		}
		else
		{
			FName BoneName = TEXT("Bone_Sword_47");
			
			FTransform BoneTransform = MeshComp->GetSocketTransform(BoneName, RTS_World);
			FVector BoneLocation = BoneTransform.GetLocation();
			BoneLocation.X = 0;
			BoneLocation.Y -= 200;
			
			bossEnemyIns->SpawnBullet(BoneLocation);
		}
	}
}
