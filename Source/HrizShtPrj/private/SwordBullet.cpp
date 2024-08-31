// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordBullet.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ZakoEnemy.h"

ASwordBullet::ASwordBullet()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SwordComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Sword Collision"));
	SwordComp->SetupAttachment(capsuleComp);

	SwordComp->SetCollisionProfileName(TEXT("SwordBullet"));
	BulletDamage = 33.f;
}

void ASwordBullet::BeginPlay()
{
	Super::BeginPlay();
	
	SwordComp->OnComponentBeginOverlap.AddDynamic(this, &ASwordBullet::OnSwordOverlap);
}

void ASwordBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Super::ShootSkill(DeltaTime);
}

void ASwordBullet::ShootSkill(float deltaTime)
{

}

void ASwordBullet::OnSwordOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	AZakoEnemy* enemy = Cast<AZakoEnemy>(OtherActor);

	if (enemy != nullptr)
	{
		UGameplayStatics::ApplyDamage(enemy, BulletDamage, nullptr, this, DamageType);
	}

	Destroy();
}
