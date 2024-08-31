// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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
	
	UPROPERTY(EditAnywhere, Category = "OptionInit")
	class UCapsuleComponent* capsComp;

	UPROPERTY(EditAnywhere, Category = "OptionInit")
	class UArrowComponent* firePosition;

	UPROPERTY(EditAnywhere, Category = "OptionInit")
	class UStaticMeshComponent* skelMeshComp;

	UPROPERTY(EditAnywhere, Category="OptionInit")
	TSubclassOf<class AEnemyBullet> bullet;

	UPROPERTY(EditAnywhere, Category="OptionInit")
	int32 health = 100;

	UPROPERTY(EditAnywhere, Category="OptionInit")
	float moveSpd = 500;

	UPROPERTY(EditAnywhere, Category="OptionInit")
	float attackDelay = 3;

	UPROPERTY(EditAnywhere, Category="Pattern")
	bool isFire = false;

	UPROPERTY(EditAnywhere, Category = "Pattern")
	bool isTrace = false;

	UFUNCTION()
	void OnBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	APawn* player;
	
	void attackPlayer(float DeltaTime);
	void hit(float Damage);
	void death();

	void moving(FVector pointPos, float DeltaTime);
	void tracePlayer(float DeltaTime);
	void escapeMap(FVector escapeDir, float DeltaTime);
	void rotatePlayer(float DeltaTime);

	float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	float currentTime = 0;
	FVector direction;

};
