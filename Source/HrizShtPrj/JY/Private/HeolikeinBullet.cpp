// Fill out your copyright notice in the Description page of Project Settings.


#include "HeolikeinBullet.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy_TEST.h"

AHeolikeinBullet::AHeolikeinBullet()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // 초기화
    IsStopped = false;
    HeolikeinComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("PunchCollision"));
    HeolikeinComp->SetupAttachment(capsuleComp);

    HeolikeinComp->SetCollisionProfileName(TEXT("KeinBullet"));

    BulletDamage = 100.f;
    DamageInterval = 1.f;
}

void AHeolikeinBullet::BeginPlay()
{
	Super::BeginPlay();

    HeolikeinComp->OnComponentBeginOverlap.AddDynamic(this, &AHeolikeinBullet::OnHeolikeinOverlap);
   
}

void AHeolikeinBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ShootSkill(DeltaTime);
}

void AHeolikeinBullet::ShootSkill(float deltaTime)
{

    if (!IsStopped)
    {
        // DeltaTime을 사용해 총알의 속도로 거리를 계산하고 이동
        FVector newLocation = GetActorLocation() + GetActorForwardVector() * Speed * deltaTime;
        SetActorLocation(newLocation);

        CurrentTime += deltaTime;

        if (CurrentTime >= DelayTime)
        {
            IsStopped = true;

            GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this, &AHeolikeinBullet::DestroyBullet, DelayTime, false);
        } 
       
    }
}

void AHeolikeinBullet::DestroyBullet()
{
    Destroy();
    GetWorld()->GetTimerManager().ClearTimer(DestroyTimerHandle);
    GetWorld()->GetTimerManager().ClearTimer(DamageTimerHandle);
}


void AHeolikeinBullet::OnHeolikeinOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
    bool bFromSweep, const FHitResult& SweepResult)
{
    AEnemy_TEST* enemy = Cast<AEnemy_TEST>(OtherActor);

    if (enemy != nullptr)
    {
        // 어러 적에게 개별 타이머를 설정하기 위해 적과 타이머 핸들 쌍을 저장
        
        FTimerDelegate TimerDelegate;

        // 데미지 타이머가 실행될 때 enemy 객체에 데미지를 적용하도록 함수를 바인딩
        TimerDelegate.BindUObject(this, &AHeolikeinBullet::ApplyDamage, enemy);
        // 일정 시간마다 데미지를 주도록 타이머 설정
        GetWorldTimerManager().SetTimer(DamageTimerHandle, TimerDelegate, DamageInterval, true);
        
        if (!Target.Contains(enemy))
        {
            Target.Add(enemy);
        }
        
    }
}

void AHeolikeinBullet::ApplyDamage(class AEnemy_TEST* enemy)
{
    for (int32 i = Target.Num() - 1; i >= 0; i--)
    {
        AEnemy_TEST* enemy = Target[i];
        if (enemy != nullptr && enemy->IsValidLowLevel())
        {
            UGameplayStatics::ApplyDamage(enemy, BulletDamage, nullptr, this, DamageType);
        }
        else
        {
            // 적이 유효하지 않으면 배열에서 제거
            Target.RemoveAt(i);
        }
    }
    
}

