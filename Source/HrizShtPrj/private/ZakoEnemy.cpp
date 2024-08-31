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
	
	//·çÆ® Ä¸½¶ ÄÄÆ÷³ÍÆ®
	capsComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Root Caplsule Component"));
	SetRootComponent(capsComp);

	//ÀÚ½Ä ½ºÄÌ·¹Å» ¸Þ½Ã ÄÄÆ÷³ÍÆ®
	skelMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	skelMeshComp->SetupAttachment(capsComp);
	
	//Åº¸· Arrow ÄÄÆ÷³ÍÆ®
	firePosition = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Component"));
	firePosition->SetupAttachment(capsComp);

	firePosition->SetRelativeLocation(FVector(50.0f, 0.0f, 0.0f));

	capsComp->SetCollisionProfileName(TEXT("Enemy"));
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

	if (player != nullptr)
	{
		direction = player->GetActorLocation() - this->GetActorLocation();
		direction.Normalize();

		capsComp->OnComponentBeginOverlap.AddDynamic(this, &AZakoEnemy::OnBulletOverlap);
	}
	
}

// Called every frame
void AZakoEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (player != nullptr && IsValid(player))
	{
		if (isFire)
		{
			this->attackPlayer(DeltaTime);
		}

		if (isTrace)
		{
			this->tracePlayer(DeltaTime);
		}
	}
	
}

void AZakoEnemy::attackPlayer(float DeltaTime)
{
	this->rotatePlayer(DeltaTime);

	if (currentTime > attackDelay)
	{
		currentTime = 0;
		AEnemyBullet* spawnBullet = GetWorld()->SpawnActor<AEnemyBullet>(bullet, GetActorLocation(), GetActorRotation());
	} 
	else
	{
		currentTime += DeltaTime;
	}
}


void AZakoEnemy::hit(float Damage)
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

/*
float AZakoEnemy::takeDmg(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float dmg = SuperTakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	UE_LOG(LogTemp, Warning, TEXT("%.2f"), dmg);
	hit(dmg);
	
	return dmg;
}*/

float AZakoEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float HitDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	// Ã¼·Â °ü¸®
	hit(HitDamage);

	return HitDamage;
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