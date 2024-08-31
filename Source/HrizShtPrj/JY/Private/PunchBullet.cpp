// Fill out your copyright notice in the Description page of Project Settings.


#include "PunchBullet.h"
#include "Components/CapsuleComponent.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy_TEST.h"

APunchBullet::APunchBullet()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PunchComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("PunchCollision"));
	PunchComp->SetupAttachment(capsuleComp);

	PunchComp->SetCollisionProfileName(TEXT("PunchBullet"));

	BulletDamage = 33.f;
}

void APunchBullet::BeginPlay()
{
	Super::BeginPlay();

	PunchComp->OnComponentBeginOverlap.AddDynamic(this, &APunchBullet::OnPunchOverlap);
}

void APunchBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Super::ShootSkill(DeltaTime);
}

void APunchBullet::ShootSkill(float deltaTime)
{

}

void APunchBullet::OnPunchOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemy_TEST* enemy = Cast<AEnemy_TEST>(OtherActor);

	if (enemy != nullptr)
	{
		UGameplayStatics::ApplyDamage(enemy, BulletDamage, nullptr, this, DamageType);
	}
	Destroy();
}
