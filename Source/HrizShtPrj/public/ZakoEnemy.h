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
	
	void attackPlayer(float DeltaTime);
	void hit(int Damage);
	void death();

	void moving(FVector pointPos, bool isTrace);
	void tracePlayer();
	void escapeMap(FVector direction);

private:
	float currentTime = 0;

};
