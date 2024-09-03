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
	void AddScore(int32 point);
	void SaveScoreData(int32 SaveValue);
	int32 LoadScoreData();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UPlayerHUD> playerHUD;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UGameOverUI> GameOverUI;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class USaveGame> saveGameclass;
	void GameOver();

protected:
	virtual void BeginPlay() override;

private:
	int32 CurrentScore = 0;
	int32 HighScore;

	// 현재 뷰 포트에 로드된 위젯 저장용 변수
	class UPlayerHUD* mainUI;
	class UGameOverUI* gameover;

	void PrintScore();
	FString dataName;
};
