// Fill out your copyright notice in the Description page of Project Settings.


#include "FighterPlayer.h"
#include "Components/ArrowComponent.h"
#include "PlayerBullet.h"
#include "Kismet/GameplayStatics.h"
#include "HeolikeinBullet.h"


void AFighterPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void AFighterPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFighterPlayer::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AFighterPlayer::FireJ()
{
	// �Ѿ� �������Ʈ ������ firePosition ��ġ�� �����Ѵ�.
	APlayerBullet* bullet = GetWorld()->SpawnActor<APlayerBullet>(bulletFactory,
		firePosition->GetComponentLocation(),
		firePosition->GetComponentRotation());
}

void AFighterPlayer::FireK()
{

	if (bulletFactory != nullptr)
	{
		// �߻��� ����� ����
		TArray<FVector> Directions;
		Directions.Emplace(FVector(0, 1, 0));
		Directions.Emplace(FVector(0, 1, 0));  
		Directions.Emplace(FVector(0, 1, 0));  
		Directions.Emplace(FVector(0, 1, 0));  
		Directions.Emplace(FVector(0, 1, 0));  

		// �� �������� �Ѿ� �߻�
		for (const FVector& Direction : Directions)
		{
			// PlayerBullet �ν��Ͻ� ����
			FActorSpawnParameters SpawnParams;
			FVector SpawnLocation = firePosition->GetComponentLocation();
			SpawnLocation.Z = FMath::RandRange(-300.f, 300.f);
			FRotator SpawnRotation = Direction.Rotation();  // ���⿡ ���� ȸ�� ����

			// PlayerBullet Ŭ������ �ν��Ͻ��� ����
			APlayerBullet* Bullet = GetWorld()->SpawnActor<APlayerBullet>(bulletFactory, SpawnLocation, SpawnRotation, SpawnParams);
			if (Bullet != nullptr)
			{
				Bullet->BulletDamage = 30.f;
				// ������ �Ѿ��� PlayerBullet�� �ڽ� Ŭ�������, �ش� Ŭ�������� �������̵�� ShootSkillL �޼��尡 ȣ���
				Bullet->ShootSkill(GetWorld()->DeltaTimeSeconds);
			}
		}
	}
}

void AFighterPlayer::FireL()
{
	// �Ѿ� �������Ʈ ������ firePosition ��ġ�� �����Ѵ�.
	AHeolikeinBullet* bullet = GetWorld()->SpawnActor<AHeolikeinBullet>(KeinBullet,
		firePosition->GetComponentLocation(),
		firePosition->GetComponentRotation());

	if (bullet != nullptr)
	{
		// ���� ������ ����
	}
}