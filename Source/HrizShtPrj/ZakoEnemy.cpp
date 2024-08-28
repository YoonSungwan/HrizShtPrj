// Fill out your copyright notice in the Description page of Project Settings.


#include "ZakoEnemy.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "EnemyBullet.h"

// Sets default values
AZakoEnemy::AZakoEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//·çÆ® Ä¸½¶ ÄÄÆ÷³ÍÆ®
	capsComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Root Caplsule Component"));
	SetRootComponent(capsComp);

	//ÀÚ½Ä ½ºÄÌ·¹Å» ¸Þ½Ã ÄÄÆ÷³ÍÆ®
	skelMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh Component"));
	skelMeshComp->SetupAttachment(capsComp);

}

// Called when the game starts or when spawned
void AZakoEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AZakoEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AZakoEnemy::attackPlayer()
{
	if (currentTime > attackDelay) {
		currentTime = 0;
		AEnemyBullet* spawnBullet = GetWorld()->SpawnActor<AEnemyBullet>(bullet, GetActorLocation(), GetActorRotation());
	}
}

void AZakoEnemy::hit(int Damage)
{
	health -= Damage;

	if (health <= 0) {
		AZakoEnemy::death();
	}
}

void AZakoEnemy::death()
{
	if (health > 0) {
		return;
	}

	isDead = true;
	AZakoEnemy::Destroy();

}
