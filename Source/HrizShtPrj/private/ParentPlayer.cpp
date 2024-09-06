// Fill out your copyright notice in the Description page of Project Settings.


#include "ParentPlayer.h"
#include "PlayerHUD.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/ArrowComponent.h"
#include "JY_GameModeBase.h"
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

	skmeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Character"));
	skmeshComp->SetupAttachment(capComp);

	firePosition = CreateDefaultSubobject<UArrowComponent>(TEXT("Fire PositionFront"));
	firePosition->SetupAttachment(capComp);
	firePosition->SetWorldRotation(FRotator(0.f, 90.f, 0.f));

	capComp->SetCollisionProfileName(TEXT("Player"));
	skmeshComp->SetCollisionProfileName(TEXT("NoCollision"));

	CurrentHealth = MaxHealth;
}

// Called when the game starts or when spawned
void AParentPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	// ���� �÷��̾ ������ ��Ʈ�ѷ��� �����´�.
	APlayerController* pc = GetWorld()->GetFirstPlayerController();

	// ���� �÷��̾� ��Ʈ�ѷ� ������ ���� ��� �ִٸ�...
	if (pc != nullptr)
	{
		// �÷��̾� ��Ʈ�ѷ��κ��� �Է� ���� �ý��� ������ �����´�.
		UEnhancedInputLocalPlayerSubsystem* subsys =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());

		if (subsys != nullptr)
		{
			// �Է� ���� �ý��� IMC ���� ������ �����Ѵ�.
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
	
	// �����ġ ������Ʈ
	if (playerHUD != nullptr)
	{
		float stopwatch = GetWorld()->GetTimeSeconds();
		playerHUD->UpdateStopWatch(stopwatch);
	}

	// Update CoolDowns
	UpdateSkillCooldown(DeltaTime);

	if (playerHUD != nullptr)
	{
		playerHUD->UpdateJSkillCoolDown(GetJSkillCooldownRatio());
		playerHUD->UpdateKSkillCoolDown(GetKSkillCooldownRatio());
		playerHUD->UpdateLSkillCoolDown(GetLSkillCooldownRatio());
	}
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
			&AParentPlayer::TryFireJ);
		enhancedInputComponent->BindAction(IA_KSkill, ETriggerEvent::Started, this,
			&AParentPlayer::TryFireK);
		enhancedInputComponent->BindAction(IA_LSkill, ETriggerEvent::Started, this,
			&AParentPlayer::TryFireL);
	}

}

float AParentPlayer::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (bIsInvincible)
	{
		// ���� ������ ���� �������� ����
		return 0.0f;
	}

	float HitDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	// ü�� ����
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
		if (playerHUD != nullptr)
		{
			playerHUD->UpdateHealth(Lives);
		}

		// ���� ���¸� �����ϰ� �����̱� ����
		StartInvincibility(3.0f);
	
	}

	else
	{
		CurrentHealth = 0.f;
		playerHUD->UpdateHealth(0);
		Destroy();
		
		AJY_GameModeBase* GameMode = Cast<AJY_GameModeBase>(GetWorld()->GetAuthGameMode());

		if (GameMode != nullptr)
		{
			GameMode->GameOver();
		}
	}
}

void AParentPlayer::SetHUD(class UPlayerHUD* hud)
{
	playerHUD = hud;
	
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
	JSkillCooldown = JSkillMaxCooldown;
	bcanFireJ = false;	// ��Ÿ�� ���� ��ų �ߵ� ��Ȱ��ȭ
}

void AParentPlayer::FireK()
{
	KSkillCooldown = KSkillMaxCooldown;
	bcanFireK = false;	// ��Ÿ�� ���� ��ų �ߵ� ��Ȱ��ȭ
	
}

void AParentPlayer::FireL()
{
	LSkillCooldown = LSkillMaxCooldown;
	bcanFireL = false;	// ��Ÿ�� ���� ��ų �ߵ� ��Ȱ��ȭ
}

void AParentPlayer::TryFireJ()
{
	if (bcanFireJ && JSkillCooldown <= 0.0f)
	{
		FireJ();
	}
}

void AParentPlayer::TryFireK()
{
	if (bcanFireK && KSkillCooldown <= 0.0f)
	{
		FireK();
	}
}

void AParentPlayer::TryFireL()
{
	if (bcanFireL && LSkillCooldown <= 0.0f)
	{
		FireL();
	}
}

void AParentPlayer::UpdateSkillCooldown(float DeltaTime)
{
	if (JSkillCooldown > 0.0f)
	{
		JSkillCooldown -= DeltaTime;

		if (JSkillCooldown <= 0.0f)
		{
			JSkillCooldown = 0.0f;
			bcanFireJ = true;	// ��Ÿ�� ������ �ߵ� ����
		}
	}


	if (KSkillCooldown > 0.0f)
	{
		KSkillCooldown -= DeltaTime;

		if (KSkillCooldown <= 0.0f)
		{
			KSkillCooldown = 0.0f;
			bcanFireK = true;	// ��Ÿ�� ������ �ߵ� ����
		}
	}

	if (LSkillCooldown > 0.0f)
	{
		LSkillCooldown -= DeltaTime;
		if (LSkillCooldown <= 0.0f)
		{
			LSkillCooldown = 0.0f;
			bcanFireL = true;	// ��Ÿ�� ������ �ߵ� ����
		}
	}
}

FString AParentPlayer::GetPlayerType() const
{
	return PlayerType;
}

void AParentPlayer::Blink()
{
	bool bIsCurrentlyVisible = !IsHidden();
	SetActorHiddenInGame(bIsCurrentlyVisible);
}

void AParentPlayer::StartInvincibility(float Duration)
{
	bIsInvincible = true;

	capComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Ignore);
	capComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Ignore);
	// SetActorEnableCollision(false);	// �浹 ��Ȱ��ȭ
	StartBlinking(Duration);

	// ���� ���� ���� Ÿ�̸� ����
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_Invincibility, this, &AParentPlayer::EndInvincibility, Duration, false);
}

void AParentPlayer::EndInvincibility()
{
	bIsInvincible = false;
	capComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	capComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	// SetActorEnableCollision(true); // �浹 �ٽ� Ȱ��ȭ
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Blink);	// ������ Ÿ�̸� ����
	SetActorHiddenInGame(false);	// ������ ������ �ٽ� ���̰� ����
}

void AParentPlayer::StartBlinking(float Duration)
{
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_Blink, this, &AParentPlayer::Blink, 0.2f, true, 0.0f);
	// GetWorld()->GetTimerManager().SetTimer(TimerHandle_Invincibility, this, &AParentPlayer::EndInvincibility, 2.0f, false);
}

