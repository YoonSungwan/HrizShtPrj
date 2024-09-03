// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/ArrowComponent.h"
#include "SwordBullet.h"
#include "PlayerBullet.h"

void ASwordPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void ASwordPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASwordPlayer::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ASwordPlayer::FireJ()
{
	Super::FireJ();
	// 총알 블루프린트 파일을 firePosition 위치에 생성한다.
	FActorSpawnParameters SpawnParams;
	SpawnParams.bNoFail = true;
	APlayerBullet* bullet = GetWorld()->SpawnActor<APlayerBullet>(bulletFactory,
		firePosition->GetComponentLocation(),
		firePosition->GetComponentRotation(),
		SpawnParams);
}

void ASwordPlayer::FireK()
{
	Super::FireK();
	if (bulletFactory != nullptr)
	{
		// 발사할 방향들 설정
		TArray<FVector> Directions;
		Directions.Emplace(FVector(0, 1, 1));   // 오른쪽
		Directions.Emplace(FVector(0, 1, -1));  // 아래쪽
		Directions.Emplace(FVector(0, 1, 0));  // 전방

		// 각 방향으로 총알 발사
		for (const FVector& Direction : Directions)
		{
			// PlayerBullet 인스턴스 생성
			FActorSpawnParameters SpawnParams;
			SpawnParams.bNoFail = true;
			FVector SpawnLocation = firePosition->GetComponentLocation();
			FRotator SpawnRotation = Direction.Rotation();  // 방향에 따른 회전 설정

			// PlayerBullet 클래스의 인스턴스를 생성
			APlayerBullet* Bullet = GetWorld()->SpawnActor<APlayerBullet>(bulletFactory, SpawnLocation, SpawnRotation);
			// UE_LOG(LogTemp, Warning, TEXT("%s"), *SpawnLocation.ToString());
			if (Bullet)
			{
				Bullet->BulletDamage = 35.f;
				// 생성된 총알이 PlayerBullet의 자식 클래스라면, 해당 클래스에서 오버라이드된 ShootSkillL 메서드가 호출됨
				Bullet->ShootSkill(GetWorld()->DeltaTimeSeconds);
			}
		}
	}
}

void ASwordPlayer::FireL()
{
	Super::FireL();
	if (bulletFactory != nullptr)
	{
		// 발사할 방향들 설정
		TArray<FVector> Directions;
		Directions.Emplace(FVector(0, 1, 0));   // 오른쪽
		Directions.Emplace(FVector(0, -1, 0));  // 왼쪽
		Directions.Emplace(FVector(0, 0, 1));   // 위쪽
		Directions.Emplace(FVector(0, 0, -1));  // 아래쪽
		Directions.Emplace(FVector(0, -1, 1));  // 왼쪽 위 대각선
		Directions.Emplace(FVector(0, -1, -1));  // 왼쪽 아래 대각선
		Directions.Emplace(FVector(0, 1, 1));  // 오른쪽 위 대각선
		Directions.Emplace(FVector(0, 1, -1));  // 오른쪽 아래 대각선

		// 각 방향으로 총알 발사
		for (const FVector& Direction : Directions)
		{
			// PlayerBullet 인스턴스 생성
			FActorSpawnParameters SpawnParams;
			SpawnParams.bNoFail = true;
			FVector SpawnLocation = firePosition->GetComponentLocation();
			FRotator SpawnRotation = Direction.Rotation();  // 방향에 따른 회전 설정

			// PlayerBullet 클래스의 인스턴스를 생성
			APlayerBullet* Bullet = GetWorld()->SpawnActor<APlayerBullet>(bulletFactory, SpawnLocation, SpawnRotation, SpawnParams);
			if (Bullet)
			{
				Bullet->BulletDamage = 100.f;
				// 생성된 총알이 PlayerBullet의 자식 클래스라면, 해당 클래스에서 오버라이드된 ShootSkillL 메서드가 호출됨
				Bullet->ShootSkill(GetWorld()->DeltaTimeSeconds);
			}
		}
	}
}

void ASwordPlayer::TryFireL()
{
	if (bcanFireL && LSkillCooldown <= 0.0f)
	{
		FireLRepeated(); // FireLRepeated는 L 스킬의 재발사 로직을 포함함
	}
}

void ASwordPlayer::FireLRepeated()
{
	FireL();  // 첫 번째 발사
	FireCount = 1;  // 발사 횟수 초기화

	// 나머지 2번의 발사를 위한 타이머 설정
	GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &ASwordPlayer::FireLRepeated_Helper, 0.8f, true);
}

void ASwordPlayer::FireLRepeated_Helper()
{
	if (FireCount < 3)  // 총 3번 발사되도록 제어
	{
		FireL();  // 추가 발사
		FireCount++;
	}
	else
	{
		// 타이머를 멈추고 발사 횟수 초기화
		GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
		FireCount = 0;
	}
}
