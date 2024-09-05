// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParentPlayer.h"
#include "FighterPlayer.generated.h"

/**
 * 
 */
UCLASS()
class HRIZSHTPRJ_API AFighterPlayer : public AParentPlayer
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	AFighterPlayer();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	virtual void FireJ() override;
	virtual void FireK() override;
	virtual void FireL() override;

public:
	// 총알 블루프린트
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AHeolikeinBullet> KeinBullet;

	UPROPERTY(EditAnywhere)
	class USoundBase* punchSound;

	UPROPERTY(EditAnywhere)
	class USoundBase* HeolikeinSound;
};
