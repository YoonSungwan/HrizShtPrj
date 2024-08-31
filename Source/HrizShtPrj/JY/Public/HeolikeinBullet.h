// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBullet.h"
#include "HeolikeinBullet.generated.h"

/**
 * 
 */
UCLASS()
class HRIZSHTPRJ_API AHeolikeinBullet : public APlayerBullet
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AHeolikeinBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ShootSkill(float deltaTime) override;

	void DestroyBullet();

	

	UFUNCTION()
	void OnHeolikeinOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	
public:
	UPROPERTY(EditAnywhere)
	class UCapsuleComponent* HeolikeinComp;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* particle;

	UPROPERTY(EditAnywhere)
	float DamageInterval;

	UPROPERTY(EditAnywhere)
    float Speed = 50.0f;   // 총알의 속도 (속도를 임의로 지정 가능)

	

private:
	
	void ApplyDamage(class AEnemy_TEST* enemy);

	float CurrentTime = 0.0f;
	float DelayTime = 5.f;      // 시간(초)
	bool IsStopped;         // 총알이 멈췄는지 여부

	FTimerHandle DamageTimerHandle;
	FTimerHandle DestroyTimerHandle;  // 총알을 제거하기 위한 타이머 핸들
	
	TArray<class AEnemy_TEST*> Target;	// 충돌한 적들을 저장하는 배열
	
};
