// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFactory.h"

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
}

// Called every frame
void AEnemyFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(currentTime > spawnDelay)
	{
		currentTime = 0;
		AZakoEnemy* spawnE = GetWorld()->SpawnActor<AZakoEnemy>(enemy, GetActorLocation(), GetActorRotation());
		spawnCount++;
	}
	else
	{
		currentTime += DeltaTime;	
	}

	if (maxSpawn <= spawnCount)
	{
		this->Destroy();
	}

}
