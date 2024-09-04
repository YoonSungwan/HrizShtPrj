// Fill out your copyright notice in the Description page of Project Settings.

#include "JY_GameModeBase.h"
#include "PlayerHUD.h"
#include "GameOverUI.h"
#include "ParentPlayer.h"
#include "SwordPlayer.h"
#include "FighterPlayer.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "SaveData.h"
#include "GI_PlayerGame.h"


void AJY_GameModeBase::AddScore(int32 point)
{
	CurrentScore += point;

	if (CurrentScore > HighScore)
	{
		HighScore = CurrentScore;
		SaveScoreData(HighScore);
	}

	PrintScore();
}

void AJY_GameModeBase::SaveScoreData(int32 SaveValue)
{
	saveGameclass = USaveData::StaticClass();

	USaveData* saveGameInstance = Cast<USaveData>(UGameplayStatics::CreateSaveGameObject(saveGameclass));

	if (saveGameInstance != nullptr)
	{
		// score 데이터를 저장할 값을 설정
		saveGameInstance->ScoreData = SaveValue;

		// 게임 데이터를 슬롯에 저장한다.
		dataName = TEXT("HighScoreData");
		UGameplayStatics::SaveGameToSlot(saveGameInstance, dataName, 0);
	}
}

int32 AJY_GameModeBase::LoadScoreData()
{
	// 저장된 게임 데이터를 불러옵니다.
	if (UGameplayStatics::DoesSaveGameExist(dataName, 0))
	{
		USaveGame* LoadedGame = UGameplayStatics::LoadGameFromSlot(dataName, 0);

		// 로드된 게임 데이터를 USaveData로 캐스팅합니다.
		USaveData* SaveDataInstance = Cast<USaveData>(LoadedGame);

		if (SaveDataInstance != nullptr)
		{
			// 로드된 데이터에서 ScoreData 값을 HighScore에 할당합니다.
			HighScore = SaveDataInstance->ScoreData;
			return HighScore;
		}
	}
	return 0;
}

void AJY_GameModeBase::GameOver()
{
	if (GameOverUI != nullptr)
	{
		gameover = CreateWidget<UGameOverUI>(GetWorld(), GameOverUI);

		if (gameover != nullptr)
		{
			gameover->AddToViewport();
			if (mainUI != nullptr)
			{
				mainUI->RemoveFromParent();
				APlayerController* pc = GetWorld()->GetFirstPlayerController();
				pc->SetShowMouseCursor(true);
				UGameplayStatics::SetGamePaused(GetWorld(), true);
			}
		}
	}
}

void AJY_GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly inputMode;
	GetWorld()->GetFirstPlayerController()->SetInputMode(inputMode);

	HighScore = LoadScoreData();

	if (playerHUD != nullptr)
	{
		mainUI = CreateWidget<UPlayerHUD>(GetWorld(), playerHUD);

		if (mainUI != nullptr)
		{
			mainUI->AddToViewport();
		}

		// 플레이어 캐릭터를 찾고 HUD를 설정
		for (TActorIterator<AParentPlayer> player(GetWorld()); player; ++player)
		{
			AParentPlayer* playerCharacter = *player;
			if (playerCharacter)
			{
				playerCharacter->SetHUD(mainUI);
			}
		}
	}
}

void AJY_GameModeBase::PrintScore()
{
	if (mainUI != nullptr)
	{
		mainUI->ScoreData->SetText(FText::AsNumber(CurrentScore));
		mainUI->HighScoreData->SetText(FText::AsNumber(HighScore));
	}
}

