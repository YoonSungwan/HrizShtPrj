// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyBullet.generated.h"

UCLASS()
class HRIZSHTPRJ_API AEnemyBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class UCapsuleComponent* capsComp;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* bulletComp;

	UPROPERTY(EditAnywhere)
	float attackSpeed = 500;

	UPROPERTY(EditAnywhere)
	int damage = 100;

	UPROPERTY(EditAnywhere)
	bool isTrace = false;

	void FireBullet();
	void DestoryBullet();
};
