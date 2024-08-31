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
	// 총알 블루프린트 파일을 firePosition 위치에 생성한다.
	APlayerBullet* bullet = GetWorld()->SpawnActor<APlayerBullet>(bulletFactory,
		firePosition->GetComponentLocation(),
		firePosition->GetComponentRotation());
}

void AFighterPlayer::FireK()
{

	if (bulletFactory != nullptr)
	{
		// 발사할 방향들 설정
		TArray<FVector> Directions;
		Directions.Emplace(FVector(0, 1, 0));
		Directions.Emplace(FVector(0, 1, 0));  
		Directions.Emplace(FVector(0, 1, 0));  
		Directions.Emplace(FVector(0, 1, 0));  
		Directions.Emplace(FVector(0, 1, 0));  

		// 각 방향으로 총알 발사
		for (const FVector& Direction : Directions)
		{
			// PlayerBullet 인스턴스 생성
			FActorSpawnParameters SpawnParams;
			FVector SpawnLocation = firePosition->GetComponentLocation();
			SpawnLocation.Z = FMath::RandRange(-300.f, 300.f);
			FRotator SpawnRotation = Direction.Rotation();  // 방향에 따른 회전 설정

			// PlayerBullet 클래스의 인스턴스를 생성
			APlayerBullet* Bullet = GetWorld()->SpawnActor<APlayerBullet>(bulletFactory, SpawnLocation, SpawnRotation, SpawnParams);
			if (Bullet != nullptr)
			{
				Bullet->BulletDamage = 30.f;
				// 생성된 총알이 PlayerBullet의 자식 클래스라면, 해당 클래스에서 오버라이드된 ShootSkillL 메서드가 호출됨
				Bullet->ShootSkill(GetWorld()->DeltaTimeSeconds);
			}
		}
	}
}

void AFighterPlayer::FireL()
{
	// 총알 블루프린트 파일을 firePosition 위치에 생성한다.
	AHeolikeinBullet* bullet = GetWorld()->SpawnActor<AHeolikeinBullet>(KeinBullet,
		firePosition->GetComponentLocation(),
		firePosition->GetComponentRotation());

	if (bullet != nullptr)
	{
		// 지속 데미지 적용
	}
}