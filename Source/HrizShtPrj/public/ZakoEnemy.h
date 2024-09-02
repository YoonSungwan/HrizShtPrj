// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "ZakoEnemy.generated.h"

UCLASS()
class HRIZSHTPRJ_API AZakoEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZakoEnemy();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	//초기 상태
	UPROPERTY(EditAnywhere, Category = "OptionInit")
	class UCapsuleComponent* capsComp;

	UPROPERTY(EditAnywhere, Category = "OptionInit")
	class UArrowComponent* firePosition;

	UPROPERTY(EditAnywhere, Category = "OptionInit")
	class UStaticMeshComponent* skelMeshComp;

	UPROPERTY(EditAnywhere, Category="OptionInit")
	int32 health = 100;

	UPROPERTY(EditAnywhere, Category="OptionInit")
	float attackDelay = 3;

	UPROPERTY(EditAnywhere, Category="OptionInit")
	float moveSpd = 500;

	UPROPERTY(EditAnywhere, Category = "OptionInit")
	float escapeCnt = 10.0f;

	//기본 패턴
	UPROPERTY(EditAnywhere, Category = "Pattern")
	bool isFire = false;

	UPROPERTY(EditAnywhere, Category = "Pattern")
	bool isTrace = false;


	//총알 세팅
	UPROPERTY(EditAnywhere, Category = "BulletSettings")
	TSubclassOf<class AEnemyBullet> normalBullet;

	UPROPERTY(EditAnywhere, Category = "BulletSettings")
	TSubclassOf<class AEnemyBullet> TraceBullet;

	UPROPERTY(EditAnywhere, Category = "BulletSettings")
	TSubclassOf<class AEnemyBullet> RadialBullet;

	UPROPERTY(EditAnywhere, Category = "BulletSettings")
	int32 RadialCount = 5;
	
	UPROPERTY(EditAnywhere, Category="Movement")
	class UCurveVector* MovementCurve;

	UFUNCTION()
	void OnBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	APawn* player;
	
	FTimeline MovementTimeline;
	FOnTimelineVector TimelineCallback;
	
	void attackPlayer(float DeltaTime);
	void hit(float Damage);
	void death();

	void tracePlayer(float DeltaTime);
	void rotatePlayer(float DeltaTime);

	void startEscape();
	void escapeMap(float DeltaTime);

	UFUNCTION()
	void radialPtrn();

	UFUNCTION()
	void HandleMovementProgress(FVector value);
	void SetupTimeline();
	void OnPlayerReachedEdge();

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	FTimerHandle Timer;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	float currentTime = 0;
	bool isEscape = false;
	FVector direction;
	FVector InitLoc;
	
	FTimerHandle timer;
};
