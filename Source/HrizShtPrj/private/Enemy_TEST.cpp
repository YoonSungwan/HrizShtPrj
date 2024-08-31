// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_TEST.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EngineUtils.h"
#include "PlayerBullet.h"
#include "ParentPlayer.h"
#include "HeolikeinBullet.h"

// Sets default values
AEnemy_TEST::AEnemy_TEST()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	SetRootComponent(boxComp);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	meshComp->SetupAttachment(boxComp);

	boxComp->SetCollisionProfileName(TEXT("Enemy"));
}

// Called when the game starts or when spawned
void AEnemy_TEST::BeginPlay()
{
	Super::BeginPlay();
	
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemy_TEST::OnEnemyOverlap);

	for (TActorIterator<AParentPlayer> player(GetWorld()); player; ++player)
	{
		dir = player->GetActorLocation() - GetActorLocation();
		dir.Normalize();
	}
}

// Called every frame
void AEnemy_TEST::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector newlocation = GetActorLocation() + dir * _moveSpeed * DeltaTime;
	SetActorLocation(newlocation);
}

float AEnemy_TEST::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Health -= DamageAmount;

	if (Health <= 0)
	{
		Destroy();
	}

	return DamageAmount;
}

void AEnemy_TEST::OnEnemyOverlap(UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AParentPlayer* player = Cast<AParentPlayer>(OtherActor);

	if (player != nullptr)
	{
		Destroy();
	}
}

