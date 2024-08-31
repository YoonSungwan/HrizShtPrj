// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UMoveComponent::UMoveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMoveComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UMoveComponent::MovingPlayer(APawn* Owner, float deltaTime)
{
	FVector dir = FVector(0, _h, _v);
	dir.Normalize();

	FVector newLocation = Owner->GetActorLocation() + dir * _PlyaermoveSpeed * deltaTime;
	Owner->SetActorLocation(newLocation);
}


void UMoveComponent::MovingBullet(class AActor* Owner, float deltaTime)
{
	// 전방 이동
	FVector newLocation = Owner->GetActorLocation() + Owner->GetActorForwardVector() * _BulletmoveSpeed * deltaTime;
	
}

// Called every frame
void UMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

