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
    float Speed = 50.0f;   // �Ѿ��� �ӵ� (�ӵ��� ���Ƿ� ���� ����)

	

private:
	
	void ApplyDamage(class AEnemy_TEST* enemy);

	float CurrentTime = 0.0f;
	float DelayTime = 5.f;      // �ð�(��)
	bool IsStopped;         // �Ѿ��� ������� ����

	FTimerHandle DamageTimerHandle;
	FTimerHandle DestroyTimerHandle;  // �Ѿ��� �����ϱ� ���� Ÿ�̸� �ڵ�
	
	TArray<class AEnemy_TEST*> Target;	// �浹�� ������ �����ϴ� �迭
	
};
