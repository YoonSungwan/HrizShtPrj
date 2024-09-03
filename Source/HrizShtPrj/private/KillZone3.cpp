// Fill out your copyright notice in the Description page of Project Settings.


#include "KillZone3.h"
#include "Components/BoxComponent.h"

// Sets default values
AKillZone3::AKillZone3()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("KillZone3"));
	SetRootComponent(boxComp);
	boxComp->SetMobility(EComponentMobility::Static);

	boxComp->SetBoxExtent(FVector(1000.f, 2000.f, 1000.f));

	boxComp->SetCollisionProfileName(TEXT("KillZone3"));
}

// Called when the game starts or when spawned
void AKillZone3::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKillZone3::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

