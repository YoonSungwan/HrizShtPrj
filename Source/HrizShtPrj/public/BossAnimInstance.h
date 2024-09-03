// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BossAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class HRIZSHTPRJ_API UBossAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	APawn* player;
	
	UAnimMontage* PlayMontage;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UCharacterMovementComponent> charMovement;

	UPROPERTY(VisibleAnywhere)
	FVector animLoc;

	UPROPERTY(VisibleAnywhere)
	uint32 bIsIdle : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InitOption")
	FVector owingPawnLoc;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InitOption")
	int32 health = 5000;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InitOption")
	float moveSpd;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InitOption")
	bool isAttaking = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BulletSettings")
	TSubclassOf<class AEnemyBullet> normalBullet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BulletSettings")
	TSubclassOf<class AEnemyBullet> traceBullet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BulletSettings")
	TSubclassOf<class AEnemyBullet> radialBullet;
	
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
