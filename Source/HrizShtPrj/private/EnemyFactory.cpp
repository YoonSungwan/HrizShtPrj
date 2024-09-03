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

	//factory 자체 쿨타임
	GetWorldTimerManager().SetTimer(factoryHandle, this, &AEnemyFactory::setEnemySpawner, spawnInterval, true);
	GetWorldTimerManager().UnPauseTimer(factoryHandle);
}

// Called every frame
void AEnemyFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(currentCnt >= enemyMaxSpawn)
	{
		if(!GetWorldTimerManager().IsTimerActive(factoryHandle))
		{
			GetWorldTimerManager().UnPauseTimer(factoryHandle);	
		}
		return;
	}

	if(IsValid(enemy))
	{
		if(currnetTime >= enemySpawnDelay)
		{
			APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
			if (PlayerController && PlayerController->GetPawn())
			{
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
	for (int i = 0; i < 3; i++)
	{
		if(spawnHriz)
		{
			initLoc.Y = initLoc.Y + spawnRange.Y * i;
		}

		if(spawnVrtc)
		{
			initLoc.Z = initLoc.Z + spawnRange.Z * i;
		}
		spawnLocArr.Add(initLoc);
	}
	
	int32 SpawnerDelay = FMath::RandRange(3, factoryDelayRange);
	spawnInterval = (enemyMaxSpawn * enemySpawnDelay) + SpawnerDelay;
}


void AEnemyFactory::startSpawn()
{
	SetActorTickEnabled(true);
}


void AEnemyFactory::setEnemySpawner()
{
	if(timerCnt >= DestroyFactoryCnt)
	{
		this->destroySpawner();
	}
	int32 arrIdx = FMath::RandRange(0, spawnLocArr.Num() - 1);
	SetActorLocation(spawnLocArr[arrIdx]);
	
	timerCnt++;
	currentCnt = 0;
}

void AEnemyFactory::destroySpawner()
{
	GetWorldTimerManager().ClearTimer(factoryHandle);
	this->Destroy();
}