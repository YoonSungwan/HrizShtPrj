// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParentPlayer.h"
#include "SwordPlayer.generated.h"

/**
 * 
 */
UCLASS()
class HRIZSHTPRJ_API ASwordPlayer : public AParentPlayer
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	virtual void FireJ() override;
	virtual void FireK() override;
	virtual void FireL() override;

	void FireLRepeated();
	void FireLRepeated_Helper();



private:
	FTimerHandle FireTimerHandle;  // 타이머를 관리하기 위한 핸들
	int32 FireCount;  // 발사 횟수를 추적하기 위한 변수
};
