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
	
	float spawnInterval = 10.0f;
	
	UPROPERTY(EditAnywhere, Category="SpawnerOption")
	int32 DestroySpawnerCnt = 5;

	UPROPERTY(EditAnywhere, Category="SpawnerOption")
	int32 SpawnerDelay = 10;

	UPROPERTY(EditAnywhere, Category = "EnemySpawn")
	int32 enemyMaxSpawn = 5;

	UPROPERTY(EditAnywhere, Category="EnemySpawn")
	float enemySpawnDelay = 1.0f;

	UFUNCTION()
	void setEnemySpawner();
	UFUNCTION()
	void destroySpawner();

	FVector SpawnLoc;
	
private:
	float currentTime = 0;
	float randomY;

	FTimerHandle Timer;

	int32 timerCnt = 0;
	int32 enemySpawnCount = 0;
};
