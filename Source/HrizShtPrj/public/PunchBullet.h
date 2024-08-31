// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBullet.h"
#include "PunchBullet.generated.h"

/**
 * 
 */
UCLASS()
class HRIZSHTPRJ_API APunchBullet : public APlayerBullet
{
	GENERATED_BODY()
	

public:
	// Sets default values for this actor's properties
	APunchBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ShootSkill(float deltaTime) override;

	UFUNCTION()
	void OnPunchOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

public:
	UPROPERTY(EditAnywhere)
	class UCapsuleComponent* PunchComp;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* particle;
};
