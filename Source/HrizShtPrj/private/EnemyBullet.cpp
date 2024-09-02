// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBullet.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyBullet::AEnemyBullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	capsComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Root Component"));
	SetRootComponent(capsComp);

	bulletComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("static mesh Component"));
	bulletComp->SetupAttachment(capsComp);

	capsComp->SetCollisionProfileName(TEXT("EnemyBullet"));
}

// Called when the game starts or when spawned
void AEnemyBullet::BeginPlay()
{
	Super::BeginPlay();

	capsComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBullet::OnBulletOverlap);

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		player = PlayerController->GetPawn();
	}
	
}

// Called every frame
void AEnemyBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	this->FireBullet(DeltaTime);
}

// Damage Event
void AEnemyBullet::OnBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (player != nullptr && player == Cast<APawn>(OtherActor))
	{
		UGameplayStatics::ApplyDamage(OtherActor, damage, nullptr, this, nullptr);
	}
	this->Destroy();
}

// Fire Event
void AEnemyBullet::FireBullet(float DeltaTime)
{
	FVector dir = this->GetActorForwardVector();

	if (isTrace)
	{
		dir = player->GetActorLocation();
	}

	FVector newLocation = this->GetActorLocation() + dir * attackSpeed * DeltaTime;
	SetActorLocation(newLocation);
}
