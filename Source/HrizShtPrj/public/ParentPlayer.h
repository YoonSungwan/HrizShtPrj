// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "ParentPlayer.generated.h"

UCLASS()
class HRIZSHTPRJ_API AParentPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AParentPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void HandleHealth(float DamageAmount);
	void HandleLives();
	void SetHUD(class UPlayerHUD* hud);

public:

	// Capsule 컴포넌트
	UPROPERTY(EditAnywhere)
	class UCapsuleComponent* capComp;

	// mesh 컴포넌트
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere)
	class UArrowComponent* firePosition;

	// Input Mapping Context
	UPROPERTY(EditAnywhere)
	class UInputMappingContext* IMC_Player;

	// Input Action
	UPROPERTY(EditAnywhere)
	class UInputAction* IA_Horizontal;

	UPROPERTY(EditAnywhere)
	class UInputAction* IA_Vertical;

	UPROPERTY(EditAnywhere)
	class UInputAction* IA_JSkill;

	UPROPERTY(EditAnywhere)
	class UInputAction* IA_LSkill;

	UPROPERTY(EditAnywhere)
	class UInputAction* IA_KSkill;

	UPROPERTY(EditAnywhere)
	float _moveSpeed = 500.f;

	// 총알 블루프린트
	UPROPERTY(EditAnywhere)
	TSubclassOf<class APlayerBullet> bulletFactory;

protected:
	float MaxHealth = 10.0f;
	float CurrentHealth = 0.f;
	int32 Lives = 3;

protected:
	void OnInputHorizontal(const struct FInputActionValue& value);
	void OnInputVertical(const struct FInputActionValue& value);
	virtual void FireJ();
	virtual void FireK();
	virtual void FireL();

	virtual void TryFireK();
	virtual void TryFireL();

	void UpdateSkillCooldown(float DeltaTime);

protected:
	float KSkillCooldown = 0.f;
	float LSkillCooldown = 0.f;
	float KSkillMaxCooldown = 7.f;
	float LSkillMaxCooldown = 30.f;

	bool bcanFireK = true;
	bool bcanFireL = true;

public:
	inline float GetKSkillCooldownRatio() const { return KSkillCooldown / KSkillMaxCooldown; }
	inline float GetLSkillCooldownRatio() const { return LSkillCooldown / LSkillMaxCooldown; }

private:
	float _h;
	float _v;

	class UPlayerHUD* playerHUD;	// HUD 참조 추가
};
