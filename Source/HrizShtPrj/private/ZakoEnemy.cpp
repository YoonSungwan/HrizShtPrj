// Fill out your copyright notice in the Description page of Project Settings.


#include "ZakoEnemy.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Components/ArrowComponent.h"
#include "JY_GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyBullet.h"
#include "PlayerBullet.h"

// Sets default values
AZakoEnemy::AZakoEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//루트 캡슐 컴포넌트
	capsComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Root Caplsule Component"));
	SetRootComponent(capsComp);

	//자식 스켈레탈 메시 컴포넌트
	skelMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	skelMeshComp->SetupAttachment(capsComp);
	
	//탄막 Arrow 컴포넌트
	firePosition = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Component"));
	firePosition->SetupAttachment(capsComp); 

	firePosition->SetRelativeLocation(FVector(50.0f, 0.0f, 0.0f));

	capsComp->SetCollisionProfileName(TEXT("Enemy"));
}

// Called when the game starts or when spawned
void AZakoEnemy::BeginPlay()
{
	Super::BeginPlay();

	InitLoc = this->GetActorLocation();

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
	
	//등장 curve 
	if(!isTrace)
	{
		SetupTimeline();
		MovementTimeline.PlayFromStart();
	}

	//유도 공격
	if (IsValid(TraceBullet))
	{
		GetWorldTimerManager().SetTimer(trcBulHandle, this, &AZakoEnemy::tracePtrn, traceAttackDelay, true);
	}

	//방사형 공격
	if (IsValid(RadialBullet))
	{
		GetWorldTimerManager().SetTimer(radBulHandle, this, &AZakoEnemy::radialPtrn, RadialAttackDelay, true);
	}

	GetWorldTimerManager().SetTimer(timer, this, &AZakoEnemy::startEscape, escapeCnt, false);

}


// Called every frame
void AZakoEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isEscape)
	{
		this->escapeMap(DeltaTime);
		return;
	}
	
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
		else if(MovementCurve != nullptr)
		{
			MovementTimeline.TickTimeline(DeltaTime);
		}
	}
	
}

void AZakoEnemy::attackPlayer(float DeltaTime)
{
	this->rotatePlayer(DeltaTime);

	if (currentTime > normalAttackDelay)
	{
		currentTime = 0;
		if (IsValid(normalBullet))
		{
			GetWorld()->SpawnActor<AEnemyBullet>(normalBullet, firePosition->GetComponentLocation(), firePosition->GetComponentRotation());
		}
	} 
	else
	{
		currentTime += DeltaTime;
	}
}


void AZakoEnemy::hit(float Damage)
{
	this->health -= Damage;

	if (this->health <= 0) {
		this->death();
	}
}

void AZakoEnemy::death()
{
	if ((this->health) > 0) {
		return;
	}
	
	auto* gm = Cast<AJY_GameModeBase>(GetWorld()->GetAuthGameMode());
	if (gm)
	{
		gm->AddScore(distroyScore);
	}
	
	if (EmitterTemplate)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), EmitterTemplate, GetActorLocation());
	}

	this->Destroy();
}


void AZakoEnemy::tracePlayer(float DeltaTime)
{
	this->SetActorLocation(this->GetActorLocation() + (direction * DeltaTime * moveSpd));
}


void AZakoEnemy::rotatePlayer(float DeltaTime)
{
	if (player != nullptr)
	{
		FVector directionToPlayer = (player->GetActorLocation()) - (this->GetActorLocation());
		FRotator desiredRotation = directionToPlayer.Rotation();
		FRotator newRotation = FMath::RInterpTo(GetActorRotation(), desiredRotation, DeltaTime, 500);

		if (newRotation.Roll <= 120)
		{
			SetActorRotation(newRotation);
		}


	}
}


float AZakoEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float dmg = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	// 체력 관리
	hit(dmg);

	return dmg;
}

// Damage Event
void AZakoEnemy::OnBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (player != nullptr && player == Cast<APawn>(OtherActor) || Cast<APlayerBullet>(OtherActor))
	{
		UGameplayStatics::ApplyDamage(OtherActor, 50, nullptr, this, nullptr);
	}
	else
	{
		this->Destroy();
	}
}

void AZakoEnemy::startEscape()
{
	isEscape = true;
}

void AZakoEnemy::escapeMap(float DeltaTime)
{
	FVector nowLocation = GetActorLocation();
	nowLocation.Z = GetActorLocation().Z + moveSpd * DeltaTime;
	SetActorLocation(nowLocation);
}


void AZakoEnemy::SetupTimeline()
{
	if (MovementCurve)
	{
		TimelineCallback.BindUFunction(this, FName("HandleMovementProgress"));
		MovementTimeline.AddInterpVector(MovementCurve, TimelineCallback);
		MovementTimeline.SetLooping(false);
	}
}

void AZakoEnemy::HandleMovementProgress(FVector Value)
{
	FVector StartLocation = InitLoc;
	FVector EndLocation = FVector(StartLocation.X, InitLoc.Y - 500, direction.Z);
	FVector NewLocation = FMath::Lerp(StartLocation, EndLocation, Value.Y);
	SetActorLocation(NewLocation);
}

void AZakoEnemy::tracePtrn()
{
	GetWorld()->SpawnActor<AEnemyBullet>(TraceBullet, firePosition->GetComponentLocation(), firePosition->GetComponentRotation());
}

void AZakoEnemy::radialPtrn()
{
	for (int i = 0; i < RadialCount - 1; i++) {
		FRotator BulletRot = GetActorRotation();
		FRotator BulletRotMin = GetActorRotation();

		for (int j = 0; j < 2; j++)
		{
			if (j == 0)
			{
				BulletRot.Pitch += i * 18.0f;
				FVector Dir = BulletRot.Vector();
				AEnemyBullet* Bullet = GetWorld()->SpawnActor<AEnemyBullet>(RadialBullet, firePosition->GetComponentLocation(), BulletRot);
			}
			else
			{
				BulletRotMin.Pitch += i * -18.0f;
				FVector Dir = BulletRotMin.Vector();
				AEnemyBullet* Bullet = GetWorld()->SpawnActor<AEnemyBullet>(RadialBullet, firePosition->GetComponentLocation(), BulletRotMin);
			}

		}
	}
	
}
