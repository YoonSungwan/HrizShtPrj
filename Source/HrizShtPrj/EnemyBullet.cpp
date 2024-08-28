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

void AEnemyBullet::fire()
{
	if (isTrace) {
		FVector startLoc = GetActorLocation();
		
	}
}

