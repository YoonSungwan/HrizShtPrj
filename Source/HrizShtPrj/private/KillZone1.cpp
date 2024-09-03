// Fill out your copyright notice in the Description page of Project Settings.


#include "KillZone1.h"
#include "Components/BoxComponent.h"


// Sets default values
AKillZone1::AKillZone1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("KillZone1"));
	SetRootComponent(boxComp);
	boxComp->SetMobility(EComponentMobility::Static);
	
	boxComp->SetBoxExtent(FVector(50.f, 2000.f, 50.f));

	boxComp->SetCollisionProfileName(TEXT("KillZone1"));
}

// Called when the game starts or when spawned
void AKillZone1::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKillZone1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

