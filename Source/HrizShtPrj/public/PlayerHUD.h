// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class HRIZSHTPRJ_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* scoreText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* ScoreData;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* HighscoreText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock*HighScoreData;

	// 체력
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* Heart1;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* Heart2;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* Heart3;

	// 스킬 세팅
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* JSkillCooldownBar;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* KSkillCooldownBar;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* LSkillCooldownBar;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* stopWatchText = nullptr;
	
	
	void UpdateHealth(int32 Lives);
	void UpdateStopWatch(float Time);
	
	// progressBar의 비율 구하기
	void UpdateJSkillCoolDown(float Ratio);
	void UpdateKSkillCoolDown(float Ratio);
	void UpdateLSkillCoolDown(float Ratio);

protected:
	virtual void NativeConstruct() override;

private:
	class AParentPlayer* PlayerCharacter;
};
