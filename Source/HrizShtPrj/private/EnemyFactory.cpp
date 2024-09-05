// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFactory.h"

#include "ParticleHelper.h"
#include "Math/UnrealMathUtility.h"
#include "ZakoEnemy.h"

// Sets default values
AEnemyFactory::AEnemyFactory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

// Called when the game starts or when spawned
void AEnemyFactory::BeginPlay()
{
	Super::BeginPlay();

	initializeValue();
	
	GetWorldTimerManager().SetTimer(tickHandle, this, &AEnemyFactory::startSpawn, startDelay, false);
}

// Called every frame
void AEnemyFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(currentCnt >= enemyMaxSpawn)
	{
		if (!GetWorldTimerManager().IsTimerActive(factoryHandle))
		{
			this->restartSpawnTimer();
		}
		return;
	}

	if(IsValid(enemy))
	{
		if(currnetTime >= enemySpawnDelay && !GetWorldTimerManager().IsTimerActive(factoryHandle))
		{
			APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
			if (PlayerController && PlayerController->GetPawn())
			{
				if (timerCnt >= DestroyFactoryCnt)
				{
					this->destroySpawner();
					return;
				}

				GetWorld()->SpawnActor<AZakoEnemy>(enemy, GetActorLocation(), GetActorRotation());
				currnetTime = 0;
				currentCnt++;
			}
	
		}
		else
		{
			currnetTime += DeltaTime;
		}
	}
	
}


void AEnemyFactory::initializeValue()
{
	FVector initLoc = GetActorLocation();
	for (int i = 0; i < factoryLocRandom; i++)
	{
		if(spawnHriz)
		{
			initLoc.Y += (spawnRange.Y * i);
		}

		if(spawnVrtc)
		{
			initLoc.Z = (spawnRange.Z * i);
		}
		spawnLocArr.Add(initLoc);
	}
	
	//int32 SpawnerDelay = FMath::RandRange(3, factoryDelayRange);
	//factorySpawnInterval = (enemyMaxSpawn * enemySpawnDelay) + factoryDelayRange;
}


void AEnemyFactory::startSpawn()
{
	SetActorTickEnabled(true);
}

void AEnemyFactory::restartSpawnTimer()
{
	//GetWorldTimerManager().SetTimer(factoryHandle, this, &AEnemyFactory::setEnemySpawner, factorySpawnInterval, true);
	GetWorldTimerManager().SetTimer(factoryHandle, this, &AEnemyFactory::setEnemySpawner, factoryDelayRange, true);
}


void AEnemyFactory::setEnemySpawner()
{
	if (spawnHriz || spawnVrtc)
	{
		int32 arrIdx = 0;
		arrIdx = FMath::RandRange(0, spawnLocArr.Num() - 1);
		SetActorLocation(spawnLocArr[arrIdx]);
	}

	timerCnt++;
	currentCnt = 0;

	GetWorldTimerManager().ClearTimer(factoryHandle);
}

void AEnemyFactory::destroySpawner()
{
	GetWorldTimerManager().ClearTimer(factoryHandle);
	this->Destroy();
}