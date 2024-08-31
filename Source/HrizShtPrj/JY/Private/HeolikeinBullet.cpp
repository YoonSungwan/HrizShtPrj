// Fill out your copyright notice in the Description page of Project Settings.


#include "HeolikeinBullet.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy_TEST.h"

AHeolikeinBullet::AHeolikeinBullet()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // �ʱ�ȭ
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
        // DeltaTime�� ����� �Ѿ��� �ӵ��� �Ÿ��� ����ϰ� �̵�
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
        // � ������ ���� Ÿ�̸Ӹ� �����ϱ� ���� ���� Ÿ�̸� �ڵ� ���� ����
        
        FTimerDelegate TimerDelegate;

        // ������ Ÿ�̸Ӱ� ����� �� enemy ��ü�� �������� �����ϵ��� �Լ��� ���ε�
        TimerDelegate.BindUObject(this, &AHeolikeinBullet::ApplyDamage, enemy);
        // ���� �ð����� �������� �ֵ��� Ÿ�̸� ����
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
            // ���� ��ȿ���� ������ �迭���� ����
            Target.RemoveAt(i);
        }
    }
    
}

