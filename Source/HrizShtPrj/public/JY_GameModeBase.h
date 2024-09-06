// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "JY_GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class HRIZSHTPRJ_API AJY_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AJY_GameModeBase();

	void AddScore(int32 point);
	void SaveScoreData(int32 SaveValue);

	UFUNCTION(BlueprintCallable)
	int32 LoadScoreData();

	// ���� ���� ��� �Լ�
	void PlayBossMusic();

	// ���� BGM���� ���ư��� �Լ�
	void ReturnToOriginalBGM();

	void GameOver();
public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UPlayerHUD> playerHUD;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UGameOverUI> GameOverUI;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class USaveGame> saveGameclass;

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 CurrentScore = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 HighScore;
	
	UPROPERTY(EditAnywhere)
	class USoundBase* GameEndSound;
	UPROPERTY(EditAnywhere)
	class USoundBase* GamePlaySound;
	UPROPERTY(EditAnywhere)
	class USoundBase* GameBoseSound;

	// ���� ���� �ð� (50��)
	UPROPERTY(EditAnywhere)
	float BossMusicStartTime = 48.0f;

	// ���� ������ ������ ���� �������� ���ƿ��� �ð�
	UPROPERTY(EditAnywhere)
	float BossMusicDuration = 32.9f;

private:
	// ���� �� ��Ʈ�� �ε�� ���� ����� ����
	class UPlayerHUD* mainUI;
	class UGameOverUI* gameover;

	FTimerHandle BossMusicTimerHandle;
	// ���� ������ ���� �� ���� BGM���� ���ư��� Ÿ�̸� �ڵ�
	FTimerHandle BossMusicEndTimerHandle;

	void PrintScore();
	void PrintHighScore();
	FString dataName;

	class USoundBase* originBGM;
	class USoundBase* BossBGM;
};
