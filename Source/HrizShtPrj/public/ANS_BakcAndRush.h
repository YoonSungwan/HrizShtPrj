// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ANS_BakcAndRush.generated.h"

/**
 * 
 */
UCLASS()
class HRIZSHTPRJ_API UANS_BakcAndRush : public UAnimNotifyState
{
	GENERATED_BODY()
	
public :
	class UBossAnimInstance* bossEnemyIns;
	class AActor* bossEnemy;

	FVector initLoc;
	FVector backLoc;
	float bossSpd;

	float playingDuration = 3.0f;
	float ElapsedTime = 0.0f;

	UPROPERTY(EditAnywhere)
	float stepBack = 4000.0f;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
