// Fill out your copyright notice in the Description page of Project Settings.


#include "BossAnimInstance.h"
#include "EnemyBullet.h"
#include "ZakoEnemy.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

void UBossAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	player = UGameplayStatics::GetPlayerCharacter(this, 0);
}

void UBossAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UBossAnimInstance::SpawnBullet(FVector spawnLoc)
{
	if(IsValid(radialBullet))
	{
		//UE_LOG(LogTemp, Warning, TEXT("BulletLoc is %s"), *spawnLoc.ToString());
		//GetWorld()->SpawnActor<AEnemyBullet>(normalBullet, spawnLoc, FRotator::ZeroRotator);

		for (int i = 0; i < 24 - 1; i++) {
			FRotator BulletRot = FRotator(90,90,90);
			FRotator BulletRotMin = FRotator(90,90,90);

			for (int j = 0; j < 2; j++)
			{
				if (j == 0)
				{
					BulletRot.Pitch += i * 18.0f;
					FVector Dir = BulletRot.Vector();
					AEnemyBullet* Bullet = GetWorld()->SpawnActor<AEnemyBullet>(radialBullet, spawnLoc, BulletRot);
				}
				else
				{
					BulletRotMin.Pitch += i * -18.0f;
					FVector Dir = BulletRotMin.Vector();
					AEnemyBullet* Bullet = GetWorld()->SpawnActor<AEnemyBullet>(radialBullet, spawnLoc, BulletRotMin);
				}

			}
		}
	}
}

void UBossAnimInstance::FallBullet()
{
	TArray<AActor*> allActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), allActors);
	for (auto actor : allActors)
	{
		if (actor->GetName().Contains("BP_FallBulletFactory"))
		{
			fallLocArr.Add(actor->GetActorLocation());
		}
	}

	if(fallLocArr.Num() > 0)
	{
		int Fir = FMath::RandRange(0, fallLocArr.Num()-1);
		int Snd = FMath::RandRange(0, fallLocArr.Num()-1);

		if(Fir == Snd)
		{
			if(Fir + 1 > fallLocArr.Num() - 1)
			{
				Snd--;
			}
			else
			{
				Snd++;
			}
		}
	
		FRotator fallRotate = FRotator(-85,90,360);

		GetWorld()->SpawnActor<AEnemyBullet>(fallBullet, fallLocArr[Fir], fallRotate);
		GetWorld()->SpawnActor<AEnemyBullet>(fallBullet, fallLocArr[Snd], fallRotate);
	}
	
	
}

void UBossAnimInstance::AttackPanel()
{
	TArray<AActor*> allActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), allActors);
	for (auto actor : allActors)
	{
		if (actor->GetName().Contains("BP_PanelFactory"))
		{
			if(IsValid(PanelEnemy))
			{
				GetWorld()->SpawnActor<AZakoEnemy>(PanelEnemy, actor->GetActorLocation(), FRotator::ZeroRotator);
				UE_LOG(LogTemp, Warning, TEXT("Panel loc is %s"), *actor->GetActorLocation().ToString())
			}
			
		}
	}
}
