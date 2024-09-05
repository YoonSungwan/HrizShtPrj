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

	UPROPERTY(VisibleAnywhere)
	FVector animLoc;

	UPROPERTY(VisibleAnywhere)
	TArray<FVector> fallLocArr;
	
	FVector BulletLoc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InitOption")
	float animLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InitOption")
	int patternNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InitOption")
	int BeforePattern;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InitOption")
	FVector playerLoc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InitOption")
	FVector owingPawnLoc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InitOption")
	int32 health = 5000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InitOption")
	float moveSpd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InitOption")
	bool isAttaking = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InitOption")
	FVector enemyInitLoc;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BulletSettings")
	TSubclassOf<class AEnemyBullet> normalBullet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BulletSettings")
	TSubclassOf<class AEnemyBullet> fallBullet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BulletSettings")
	TSubclassOf<class AEnemyBullet> radialBullet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BulletSettings")
	TSubclassOf<class AZakoEnemy> PanelEnemy;
	
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	void SpawnBullet(FVector spawnLoc);

	UFUNCTION(BlueprintCallable)
	void FallBullet();

	UFUNCTION(BlueprintCallable)
	void AttackPanel();
};
