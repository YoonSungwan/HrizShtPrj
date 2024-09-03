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
	// �Ѿ� �������Ʈ ������ firePosition ��ġ�� �����Ѵ�.
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
		// �߻��� ����� ����
		TArray<FVector> Directions;
		Directions.Emplace(FVector(0, 1, 1));   // ������
		Directions.Emplace(FVector(0, 1, -1));  // �Ʒ���
		Directions.Emplace(FVector(0, 1, 0));  // ����

		// �� �������� �Ѿ� �߻�
		for (const FVector& Direction : Directions)
		{
			// PlayerBullet �ν��Ͻ� ����
			FActorSpawnParameters SpawnParams;
			SpawnParams.bNoFail = true;
			FVector SpawnLocation = firePosition->GetComponentLocation();
			FRotator SpawnRotation = Direction.Rotation();  // ���⿡ ���� ȸ�� ����

			// PlayerBullet Ŭ������ �ν��Ͻ��� ����
			APlayerBullet* Bullet = GetWorld()->SpawnActor<APlayerBullet>(bulletFactory, SpawnLocation, SpawnRotation);
			// UE_LOG(LogTemp, Warning, TEXT("%s"), *SpawnLocation.ToString());
			if (Bullet)
			{
				Bullet->BulletDamage = 35.f;
				// ������ �Ѿ��� PlayerBullet�� �ڽ� Ŭ�������, �ش� Ŭ�������� �������̵�� ShootSkillL �޼��尡 ȣ���
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
		// �߻��� ����� ����
		TArray<FVector> Directions;
		Directions.Emplace(FVector(0, 1, 0));   // ������
		Directions.Emplace(FVector(0, -1, 0));  // ����
		Directions.Emplace(FVector(0, 0, 1));   // ����
		Directions.Emplace(FVector(0, 0, -1));  // �Ʒ���
		Directions.Emplace(FVector(0, -1, 1));  // ���� �� �밢��
		Directions.Emplace(FVector(0, -1, -1));  // ���� �Ʒ� �밢��
		Directions.Emplace(FVector(0, 1, 1));  // ������ �� �밢��
		Directions.Emplace(FVector(0, 1, -1));  // ������ �Ʒ� �밢��

		// �� �������� �Ѿ� �߻�
		for (const FVector& Direction : Directions)
		{
			// PlayerBullet �ν��Ͻ� ����
			FActorSpawnParameters SpawnParams;
			SpawnParams.bNoFail = true;
			FVector SpawnLocation = firePosition->GetComponentLocation();
			FRotator SpawnRotation = Direction.Rotation();  // ���⿡ ���� ȸ�� ����

			// PlayerBullet Ŭ������ �ν��Ͻ��� ����
			APlayerBullet* Bullet = GetWorld()->SpawnActor<APlayerBullet>(bulletFactory, SpawnLocation, SpawnRotation, SpawnParams);
			if (Bullet)
			{
				Bullet->BulletDamage = 100.f;
				// ������ �Ѿ��� PlayerBullet�� �ڽ� Ŭ�������, �ش� Ŭ�������� �������̵�� ShootSkillL �޼��尡 ȣ���
				Bullet->ShootSkill(GetWorld()->DeltaTimeSeconds);
			}
		}
	}
}

void ASwordPlayer::TryFireL()
{
	if (bcanFireL && LSkillCooldown <= 0.0f)
	{
		FireLRepeated(); // FireLRepeated�� L ��ų�� ��߻� ������ ������
	}
}

void ASwordPlayer::FireLRepeated()
{
	FireL();  // ù ��° �߻�
	FireCount = 1;  // �߻� Ƚ�� �ʱ�ȭ

	// ������ 2���� �߻縦 ���� Ÿ�̸� ����
	GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &ASwordPlayer::FireLRepeated_Helper, 0.8f, true);
}

void ASwordPlayer::FireLRepeated_Helper()
{
	if (FireCount < 3)  // �� 3�� �߻�ǵ��� ����
	{
		FireL();  // �߰� �߻�
		FireCount++;
	}
	else
	{
		// Ÿ�̸Ӹ� ���߰� �߻� Ƚ�� �ʱ�ȭ
		GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
		FireCount = 0;
	}
}
