// Fill out your copyright notice in the Description page of Project Settings.


#include "KillZone2.h"
#include "Components/BoxComponent.h"

// Sets default values
AKillZone2::AKillZone2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("KillZone2"));
	SetRootComponent(boxComp);
	boxComp->SetMobility(EComponentMobility::Static);

	boxComp->SetBoxExtent(FVector(50.f, 2000.f, 50.f));

	boxComp->SetCollisionProfileName(TEXT("KillZone2"));
}

// Called when the game starts or when spawned
void AKillZone2::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKillZone2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

