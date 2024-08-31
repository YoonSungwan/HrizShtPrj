// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MoveComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HRIZSHTPRJ_API UMoveComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMoveComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	FVector GetMove() const { return _move; }
	void SetMove(FVector moveDirection) { _move = moveDirection; }

	float GetHorizontal() const { return _h; }
	void SetHorizontal(float h) { _h = h; }
	float GetVertical() const { return _h; }
	void SetVertical(float v) { _v = v; }

	void MovingPlayer(class APawn* Owner, float deltaTime);
	void MovingBullet(class AActor* Owner, float deltaTime);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	FVector _move;
	float _PlyaermoveSpeed = 500.f;
	float _BulletmoveSpeed = 800.f;

private:
	float _h;
	float _v;
};
