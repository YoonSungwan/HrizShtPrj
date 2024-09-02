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

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UPlayerHUD> playerHUD;

protected:
	virtual void BeginPlay() override;

private:
	int32 CurrentScore = 0;
	int32 HighScore;

	// 현재 뷰 포트에 로드된 위젯 저장용 변수
	class UPlayerHUD* mainUI;

	void PrintScore();
};
