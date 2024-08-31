// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBullet.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ZakoEnemy.h"
#include "ParentPlayer.h"


// Sets default values
APlayerBullet::APlayerBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	capsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collision"));
	SetRootComponent(capsuleComp);
	capsuleComp->SetCapsuleHalfHeight(9.f);
	capsuleComp->SetCapsuleRadius(6.f);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet Mesh"));
	meshComp->SetupAttachment(capsuleComp);
	meshComp->SetWorldScale3D(FVector(0.1f));

	meshComp->SetCollisionProfileName(TEXT("NoCollision"));
	capsuleComp->SetCollisionProfileName(TEXT("Bullet"));
	
	BulletDamage = 10.f;
}

// Called when the game starts or when spawned
void APlayerBullet::BeginPlay()
{
	Super::BeginPlay();

	meshComp->OnComponentBeginOverlap.AddDynamic(this, &APlayerBullet::OnBulletOverlap);
}

// Called every frame
void APlayerBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ShootSkill(DeltaTime);

}

void APlayerBullet::ShootSkill(float deltaTime)
{
	// 전방으로 이동할 위치를 계산한다.
	FVector newLocation = GetActorLocation() + (GetActorForwardVector() *_moveSpeed * deltaTime);

	// 계산된 위치 좌표를 액터의 새 좌표로 넣는다.
	SetActorLocation(newLocation);
}

void APlayerBullet::OnBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AZakoEnemy* enemy = Cast<AZakoEnemy>(OtherActor);

	if (enemy != nullptr)
	{
		UGameplayStatics::ApplyDamage(enemy, BulletDamage, nullptr, this, DamageType);
	}

	Destroy();
}
