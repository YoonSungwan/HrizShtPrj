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

	UPROPERTY(EditAnywhere, Category = "OptionInit")
	TSubclassOf<class AZakoEnemy> enemy;

	int32 spawnCount = 0;

	UPROPERTY(EditAnywhere, Category = "OptionInit")
	int32 maxSpawn = 3;

	UPROPERTY(EditAnywhere, Category="OptionInit")
	float spawnDelay = 5.0f;

private:
	float currentTime = 0;

};
