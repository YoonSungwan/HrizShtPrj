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

	// 보스 음악 재생 함수
	void PlayBossMusic();

	// 원래 BGM으로 돌아가는 함수
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

	// 보스 등장 시간 (50초)
	UPROPERTY(EditAnywhere)
	float BossMusicStartTime = 48.0f;

	// 보스 음악이 끝나고 원래 음악으로 돌아오는 시간
	UPROPERTY(EditAnywhere)
	float BossMusicDuration = 32.9f;

private:
	// 현재 뷰 포트에 로드된 위젯 저장용 변수
	class UPlayerHUD* mainUI;
	class UGameOverUI* gameover;

	FTimerHandle BossMusicTimerHandle;
	// 보스 음악이 끝난 후 원래 BGM으로 돌아가는 타이머 핸들
	FTimerHandle BossMusicEndTimerHandle;

	void PrintScore();
	void PrintHighScore();
	FString dataName;

	class USoundBase* originBGM;
	class USoundBase* BossBGM;
};
