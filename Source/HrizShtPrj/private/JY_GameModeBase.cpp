// Fill out your copyright notice in the Description page of Project Settings.

#include "JY_GameModeBase.h"
#include "PlayerHUD.h"
#include "GameOverUI.h"
#include "ParentPlayer.h"
#include "SwordPlayer.h"
#include "FighterPlayer.h"
#include "Components/TextBlock.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "SaveData.h"
#include "GI_PlayerGame.h"


AJY_GameModeBase::AJY_GameModeBase()
{
	dataName = TEXT("HighScoreData");
}

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
	// saveGameclass = USaveData::StaticClass();

	USaveData* saveGameInstance = Cast<USaveData>(UGameplayStatics::CreateSaveGameObject(saveGameclass));

	if (saveGameclass == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("SaveGameClass is not set!"));
		return;
	}

	if (saveGameInstance != nullptr)
	{
		// score 데이터를 저장할 값을 설정
		saveGameInstance->ScoreData = SaveValue;

		// 게임 데이터를 슬롯에 저장한다.
		
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
			UE_LOG(LogTemp, Warning, TEXT("%d"), HighScore);

			return HighScore;
		}
	}
	return 0;
}

void AJY_GameModeBase::PlayBossMusic()
{
	UAudioComponent* AudioComponent = UGameplayStatics::SpawnSound2D(GetWorld(), originBGM);

	BossBGM = GameBoseSound;
	// 원래 BGM을 멈추고 보스 BGM을 재생
	if (AudioComponent != nullptr)
	{
		AudioComponent->Stop();
	}
	UGameplayStatics::PlaySound2D(GetWorld(), BossBGM, 1.f, 1.f, 48.f);

	// 보스 BGM이 끝나면 다시 원래 BGM으로 돌아오도록 타이머 설정
	GetWorldTimerManager().SetTimer(BossMusicEndTimerHandle, this, &AJY_GameModeBase::ReturnToOriginalBGM, BossMusicDuration, false);
}

void AJY_GameModeBase::ReturnToOriginalBGM()
{
	UAudioComponent* BossComponent = UGameplayStatics::SpawnSound2D(GetWorld(), BossBGM);
	
	if (BossComponent != nullptr)
	{
		BossComponent->Stop();
		BossComponent = nullptr;
	}

	UGameplayStatics::PlaySound2D(GetWorld(), originBGM);
}

void AJY_GameModeBase::GameOver()
{
	if (GameOverUI != nullptr)
	{
		gameover = CreateWidget<UGameOverUI>(GetWorld(), GameOverUI);

		UAudioComponent* AudioComponent = UGameplayStatics::SpawnSound2D(GetWorld(), originBGM);
		// 원래 BGM을 멈추고 보스 BGM을 재생
		if (AudioComponent != nullptr)
		{
			AudioComponent->SetVolumeMultiplier(0.f);
			AudioComponent->Stop();
			AudioComponent = nullptr;
		}

		UGameplayStatics::PlaySound2D(GetWorld(), GameEndSound);

		if (gameover != nullptr)
		{
			gameover->AddToViewport();
			if (mainUI != nullptr)
			{
				mainUI->RemoveFromParent();
				APlayerController* pc = GetWorld()->GetFirstPlayerController();

				//pc->SetInputMode(FInputModeUIOnly());

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
			APlayerController* pc = GetWorld()->GetFirstPlayerController();
			pc->SetInputMode(FInputModeGameOnly());
			pc->SetShowMouseCursor(false);

			originBGM = GamePlaySound;
			UGameplayStatics::PlaySound2D(GetWorld(), originBGM);
		}


		// 보스 BGM을 위한 타이머 설정 (50초 후)
		GetWorld()->GetTimerManager().SetTimer(BossMusicTimerHandle, this, &AJY_GameModeBase::PlayBossMusic, BossMusicStartTime, false);
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
	PrintHighScore();
}

void AJY_GameModeBase::PrintScore()
{
	if (mainUI != nullptr)
	{
		mainUI->ScoreData->SetText(FText::AsNumber(CurrentScore));
	}
}

void AJY_GameModeBase::PrintHighScore()
{
	if (mainUI != nullptr)
	{
		mainUI->HighScoreData->SetText(FText::AsNumber(HighScore));
	}
}

