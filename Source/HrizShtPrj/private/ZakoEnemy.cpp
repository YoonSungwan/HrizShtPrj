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
	
	if(!isTrace)
	{
		SetupTimeline();

		if (MovementCurve)
		{
			MovementTimeline.PlayFromStart();
		}	
	}
	/*
	FVector2D viewportSize;
	GEngine->GameViewport->GetViewportSize(viewportSize);
	
	FVector2D ScreenLocation;
	PlayerController->ProjectWorldLocationToScreen(GetPawn()->GetActorLocation(), ScreenLocation);

	FVector WorldLocation, WorldDirection;
	PlayerController->DeprojectScreenPositionToWorld(0.0f, 0.0f, WorldLocation, WorldDirection);

	// 좌상단, 우하단의 월드 좌표 계산
	FVector TopLeftWorldLocation, TopLeftWorldDirection;
	PlayerController->DeprojectScreenPositionToWorld(0.0f, 0.0f, TopLeftWorldLocation, TopLeftWorldDirection);

	FVector BottomRightWorldLocation, BottomRightWorldDirection;
	PlayerController->DeprojectScreenPositionToWorld(ViewportSize.X, ViewportSize.Y, BottomRightWorldLocation, BottomRightWorldDirection);

	// 플레이어의 현재 위치를 기준으로 화면 경계 체크
	FVector PlayerLocation = GetPawn()->GetActorLocation();

	bool bIsOutsideLeft = PlayerLocation.X < TopLeftWorldLocation.X;
	bool bIsOutsideRight = PlayerLocation.X > BottomRightWorldLocation.X;
	bool bIsOutsideTop = PlayerLocation.Y > TopLeftWorldLocation.Y;
	bool bIsOutsideBottom = PlayerLocation.Y < BottomRightWorldLocation.Y;

	if (bIsOutsideLeft || bIsOutsideRight || bIsOutsideTop || bIsOutsideBottom)
	{
		// 이벤트 발생
		OnPlayerReachedEdge();
	}*/
}

void AZakoEnemy::OnPlayerReachedEdge()
{
	// 플레이어가 화면 끝에 도달했을 때 실행할 로직
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Player has reached the edge of the screen!"));
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
		else
		{
			MovementTimeline.TickTimeline(DeltaTime);
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
		this->death();
	}
}

void AZakoEnemy::death()
{
	if (health > 0) {
		return;
	}

	this->Destroy();
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
	if (player != nullptr && player == Cast<APawn>(OtherActor))
	{
		UGameplayStatics::ApplyDamage(OtherActor, 50, nullptr, this, nullptr);
	}

	this->Destroy();
}

void AZakoEnemy::HandleMovementProgress(FVector Value)
{
	FVector StartLocation = GetActorLocation();
	FVector EndLocation = FVector(0,330,50);
	FVector NewLocation = FMath::Lerp(StartLocation, EndLocation, Value.Y);
	SetActorLocation(NewLocation);
}

void AZakoEnemy::SetupTimeline()
{
	if (MovementCurve)
	{
		FOnTimelineVector TimelineCallback;
		TimelineCallback.BindUFunction(this, FName("HandleMovementProgress"));
		MovementTimeline.AddInterpVector(MovementCurve, TimelineCallback);
		MovementTimeline.SetLooping(false);
		
	}
}