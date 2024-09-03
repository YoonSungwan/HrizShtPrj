// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyFactory.generated.h"

UCLASS()
class HRIZSHTPRJ_API AEnemyFactory : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyFactory();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "EnemySpawn")
	TSubclassOf<class AZakoEnemy> enemy;

	UPROPERTY(EditAnywhere, Category = "EnemySpawn")
	FVector spawnRange = FVector(50,0,50);

	UPROPERTY(EditAnywhere, Category="EnemySpawn")
	float enemySpawnDelay = 1.0f;

	UPROPERTY(EditAnywhere, Category = "EnemySpawn")
	int32 enemyMaxSpawn = 5;

	TArray<FVector> spawnLocArr;
	
	float spawnInterval = 10.0f;

	UPROPERTY(EditAnywhere, Category="SpawnerOption")
	float startDelay = 5.0f;
	
	UPROPERTY(EditAnywhere, Category="SpawnerOption")
	int32 DestroyFactoryCnt = 5;

	UPROPERTY(EditAnywhere, Category="SpawnerOption")
	int32 factoryDelayRange = 10;

	UPROPERTY(EditAnywhere, Category="SpawnerOption")
	bool spawnHriz = false;

	UPROPERTY(EditAnywhere, Category="SpawnerOption")
	bool spawnVrtc = true;
	
	void setEnemySpawner();
	void destroySpawner();
	void startSpawn();
	
private:
	int32 timerCnt = 0;
	
	FTimerHandle tickHandle;
	FTimerHandle factoryHandle;

	int32 currentCnt = 0;
	float currnetTime = 0;
	
	void initializeValue();
};
