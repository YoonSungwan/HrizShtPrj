// Fill out your copyright notice in the Description page of Project Settings.


#include "ZakoEnemy.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyBullet.h"

// Sets default values
AZakoEnemy::AZakoEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//��Ʈ ĸ�� ������Ʈ
	capsComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Root Caplsule Component"));
	SetRootComponent(capsComp);

	//�ڽ� ���̷�Ż �޽� ������Ʈ
	skelMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh Component"));
	skelMeshComp->SetupAttachment(capsComp);

	//ź�� Arrow ������Ʈ
	firePosition = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Component"));
	firePosition->SetupAttachment(skelMeshComp);
}

// Called when the game starts or when spawned
void AZakoEnemy::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		player = PlayerController->GetPawn();
	}

	direction = player->GetActorLocation() - this->GetActorLocation();
	direction.Normalize();

	capsComp->OnComponentBeginOverlap.AddDynamic(this, &AZakoEnemy::OnBulletOverlap);

	capsComp->SetGenerateOverlapEvents(true);
	capsComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	capsComp->SetCollisionProfileName(TEXT("OverlapAll"));
}

// Called every frame
void AZakoEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isFire) 
	{
		this->attackPlayer(DeltaTime);
	}

	if (isTrace) 
	{
		this->tracePlayer(DeltaTime);
	}
	
}

void AZakoEnemy::attackPlayer(float DeltaTime)
{
	this->rotatePlayer(DeltaTime);

	if (currentTime > attackDelay)
	{
		currentTime = 0;
		AEnemyBullet* spawnBullet = GetWorld()->SpawnActor<AEnemyBullet>(bullet, GetActorLocation(), GetActorRotation());
	} else
	{
		currentTime += DeltaTime;
	}
}


void AZakoEnemy::hit(int Damage)
{
	health -= Damage;

	if (health <= 0) {
		AZakoEnemy::death();
	}
}

void AZakoEnemy::death()
{
	if (health > 0) {
		return;
	}

	AZakoEnemy::Destroy();
}


void AZakoEnemy::tracePlayer(float DeltaTime)
{
	this->SetActorLocation(this->GetActorLocation() + (direction * DeltaTime * moveSpd));
}


void AZakoEnemy::moving(FVector pointPos, float DeltaTime)
{
	this->SetActorLocation(this->GetActorLocation() + (direction * DeltaTime * moveSpd));
}


void AZakoEnemy::escapeMap(FVector escapeDir, float DeltaTime)
{
	SetActorLocation(this->GetActorLocation() + escapeDir * DeltaTime * moveSpd);
}


void AZakoEnemy::rotatePlayer(float DeltaTime)
{
	if (player != nullptr)
	{
		FVector directionToPlayer = (player->GetActorLocation()) - (this->GetActorLocation());
		FRotator desiredRotation = directionToPlayer.Rotation();
		FRotator newRotation = FMath::RInterpTo(GetActorRotation(), desiredRotation, DeltaTime, 500);

		SetActorRotation(newRotation);
	}
}


// Damage Event
void AZakoEnemy::OnBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (player != nullptr && player == Cast<APawn>(OtherActor))
	{
		UGameplayStatics::ApplyDamage(OtherActor, 50, nullptr, this, nullptr);
		this->Destroy();
	}

}