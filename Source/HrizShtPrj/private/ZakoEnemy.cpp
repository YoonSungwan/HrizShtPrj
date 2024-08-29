// Fill out your copyright notice in the Description page of Project Settings.


#include "ZakoEnemy.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Components/ArrowComponent.h"
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

	//Åº¸· Arrow ÄÄÆ÷³ÍÆ®
	firePosition = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Component"));
	firePosition->SetupAttachment(skelMeshComp);
}

// Called when the game starts or when spawned
void AZakoEnemy::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		player = PlayerController->GetPawn();
	}
}

// Called every frame
void AZakoEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	traceToPlayer(DeltaTime);;
	attackPlayer(DeltaTime);
}

void AZakoEnemy::attackPlayer(float DeltaTime)
{
	if (currentTime > attackDelay)
	{
		currentTime = 0;
		AEnemyBullet* spawnBullet = GetWorld()->SpawnActor<AEnemyBullet>(bullet, GetActorLocation(), GetActorRotation());
	} else
	{
		currentTime += DeltaTime;
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

void AZakoEnemy::traceToPlayer(float DeltaTime)
{
	FVector enemyLoc = this->GetActorLocation();
	FVector dir = (player->GetActorLocation()) - enemyLoc;
	dir.Normalize();

	this->SetActorLocation(enemyLoc + (dir * DeltaTime * moveSpd));
}