// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBullet.h"
#include "SwordBullet.generated.h"

/**
 * 
 */
UCLASS()
class HRIZSHTPRJ_API ASwordBullet : public APlayerBullet
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASwordBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ShootSkill(float deltaTime) override;

	UFUNCTION()
	void OnSwordOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

public:
	UPROPERTY(EditAnywhere)
	class UCapsuleComponent* SwordComp;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* particle;
	
};
