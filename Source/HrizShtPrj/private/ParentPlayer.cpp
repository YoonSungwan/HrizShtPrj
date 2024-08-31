// Fill out your copyright notice in the Description page of Project Settings.


#include "ParentPlayer.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/ArrowComponent.h"
#include "PlayerBullet.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AParentPlayer::AParentPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	capComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("PlayerCollision"));
	SetRootComponent(capComp);
	capComp->SetCapsuleHalfHeight(55.f);
	capComp->SetCapsuleRadius(33.f);


	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Geometry"));
	meshComp->SetupAttachment(capComp);

	firePosition = CreateDefaultSubobject<UArrowComponent>(TEXT("Fire PositionFront"));
	firePosition->SetupAttachment(capComp);
	firePosition->SetWorldRotation(FRotator(0.f, 90.f, 0.f));

	capComp->SetCollisionProfileName(TEXT("Player"));
	meshComp->SetCollisionProfileName(TEXT("NoCollision"));

	CurrentHealth = MaxHealth;
}

// Called when the game starts or when spawned
void AParentPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	// 현재 플레이어가 소유한 컨트롤러를 가져온다.
	APlayerController* pc = GetWorld()->GetFirstPlayerController();

	// 만일 플레이어 컨트롤러 변수에 값이 들어 있다면...
	if (pc != nullptr)
	{
		// 플레이어 컨트롤러로부터 입력 서브 시스템 정보를 가져온다.
		UEnhancedInputLocalPlayerSubsystem* subsys =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());

		if (subsys != nullptr)
		{
			// 입력 서브 시스템 IMC 파일 변수를 연결한다.
			subsys->AddMappingContext(IMC_Player, 0);
		}
	}
}

// Called every frame
void AParentPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector dir = FVector(0, _h, _v);
	dir.Normalize();

	FVector newLocation = GetActorLocation() + dir * _moveSpeed * DeltaTime;
	SetActorLocation(newLocation, true);
	
}

// Called to bind functionality to input
void AParentPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* enhancedInputComponent = 
		Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (enhancedInputComponent != nullptr)
	{
		enhancedInputComponent->BindAction(IA_Horizontal, ETriggerEvent::Triggered, this,
			&AParentPlayer::OnInputHorizontal);
		enhancedInputComponent->BindAction(IA_Horizontal, ETriggerEvent::Completed, this,
			&AParentPlayer::OnInputHorizontal);
		enhancedInputComponent->BindAction(IA_Vertical, ETriggerEvent::Triggered, this,
			&AParentPlayer::OnInputVertical);
		enhancedInputComponent->BindAction(IA_Vertical, ETriggerEvent::Completed, this,
			&AParentPlayer::OnInputVertical);
		enhancedInputComponent->BindAction(IA_JSkill, ETriggerEvent::Started, this,
			&AParentPlayer::FireJ);
		enhancedInputComponent->BindAction(IA_KSkill, ETriggerEvent::Started, this,
			&AParentPlayer::FireK);
		enhancedInputComponent->BindAction(IA_LSkill, ETriggerEvent::Started, this,
			&AParentPlayer::FireL);
	}

}

float AParentPlayer::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float HitDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	// 체력 관리
	HandleHealth(HitDamage);

	return HitDamage;
}

void AParentPlayer::HandleHealth(float DamageAmount)
{
	CurrentHealth -= DamageAmount;

	if (CurrentHealth <= 0)
	{
		CurrentHealth = 0.f;
		HandleLives();
	}
}

void AParentPlayer::HandleLives()
{
	if (Lives > 1)
	{
		--Lives;
		CurrentHealth = MaxHealth;
	}

	else
	{
		CurrentHealth = 0.f;
		Destroy();
	}
}

void AParentPlayer::OnInputHorizontal(const struct FInputActionValue& value)
{
	_h = value.Get<float>();
}

void AParentPlayer::OnInputVertical(const struct FInputActionValue& value)
{
	_v = value.Get<float>();
}

void AParentPlayer::FireJ()
{
	
}

void AParentPlayer::FireK()
{
	
	
}

void AParentPlayer::FireL()
{
	
}

