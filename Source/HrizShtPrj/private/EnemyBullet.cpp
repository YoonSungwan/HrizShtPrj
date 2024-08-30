// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBullet.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AEnemyBullet::AEnemyBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	capsComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Root Component"));
	SetRootComponent(capsComp);

	bulletComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("static mesh Component"));
	bulletComp->SetupAttachment(capsComp);

}

// Called when the game starts or when spawned
void AEnemyBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AEnemyBullet::FireBullet()
{
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	FVector dir = GetActorForwardVector();
	
	if (isTrace)
	{
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		APawn* player;
		if (PlayerController)
		{
			player = PlayerController->GetPawn();
			dir = player->GetActorLocation();
		}
	}

	FVector newLocation = GetActorLocation() + dir * attackSpeed * DeltaTime;
	SetActorLocation(newLocation);
	
}

