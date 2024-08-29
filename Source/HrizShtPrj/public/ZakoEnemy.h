// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZakoEnemy.generated.h"

UCLASS()
class HRIZSHTPRJ_API AZakoEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZakoEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class UCapsuleComponent* capsComp;

	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* skelMeshComp;

	UPROPERTY(EditAnywhere)
	class UArrowComponent* firePosition;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AEnemyBullet> bullet;

	UPROPERTY(EditAnywhere)
	int32 health = 100;

	UPROPERTY(EditAnywhere)
	float moveSpd = 500;

	UPROPERTY(EditAnywhere)
	float attackDelay = 3;

	UPROPERTY(EditAnywhere)
	bool isDead = false;

	APawn* player;
	
	//공격
	void attackPlayer(float DeltaTime);

	//피격
	void hit(int Damage);

	//사망
	void death();

	//이동패턴 - 플레이어 추적
	void traceToPlayer(float DeltaTime);

	//이동패턴 - 이탈

	//이동패턴 - 고정

	//이동패턴 - 고정 후 이탈


private:
	float currentTime = 0;

};
