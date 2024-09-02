// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFactory.h"
#include "Math/UnrealMathUtility.h"
#include "ZakoEnemy.h"

// Sets default values
AEnemyFactory::AEnemyFactory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyFactory::BeginPlay()
{
	Super::BeginPlay();

	SpawnLoc = GetActorLocation();
	spawnInterval = (enemyMaxSpawn * enemySpawnDelay) + SpawnerDelay;
	GetWorldTimerManager().SetTimer(Timer, this, &AEnemyFactory::setEnemySpawner, spawnInterval, true);
}

// Called every frame
void AEnemyFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(currentTime > enemySpawnDelay)
	{
		if(enemyMaxSpawn > enemySpawnCount)
		{
			currentTime = 0;
			AZakoEnemy* spawnE = GetWorld()->SpawnActor<AZakoEnemy>(enemy, GetActorLocation(), GetActorRotation());
			enemySpawnCount++;
		}

	}
	else
	{
		currentTime += DeltaTime;	
	}
	
}

void AEnemyFactory::setEnemySpawner()
{
	if(timerCnt >= DestroySpawnerCnt)
	{
		this->destroySpawner();
	}
	
	enemySpawnCount = 0;
	currentTime = 0;

	randomY = FMath::RoundToFloat(FMath::RandRange(-2.0f, 2.0f)) * 100;
	SetActorLocation(FVector(SpawnLoc.X, SpawnLoc.Y+randomY, SpawnLoc.Z));

	timerCnt++;
}

void AEnemyFactory::destroySpawner()
{
	GetWorldTimerManager().ClearTimer(Timer);
	this->Destroy();
}