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
		// score �����͸� ������ ���� ����
		saveGameInstance->ScoreData = SaveValue;

		// ���� �����͸� ���Կ� �����Ѵ�.
		
		UGameplayStatics::SaveGameToSlot(saveGameInstance, dataName, 0);
	}
}

int32 AJY_GameModeBase::LoadScoreData()
{
	// ����� ���� �����͸� �ҷ��ɴϴ�.
	if (UGameplayStatics::DoesSaveGameExist(dataName, 0))
	{
		USaveGame* LoadedGame = UGameplayStatics::LoadGameFromSlot(dataName, 0);

		// �ε�� ���� �����͸� USaveData�� ĳ�����մϴ�.
		USaveData* SaveDataInstance = Cast<USaveData>(LoadedGame);

		if (SaveDataInstance != nullptr)
		{
			// �ε�� �����Ϳ��� ScoreData ���� HighScore�� �Ҵ��մϴ�.
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
	// ���� BGM�� ���߰� ���� BGM�� ���
	if (AudioComponent != nullptr)
	{
		AudioComponent->Stop();
	}
	UGameplayStatics::PlaySound2D(GetWorld(), BossBGM, 1.f, 1.f, 48.f);

	// ���� BGM�� ������ �ٽ� ���� BGM���� ���ƿ����� Ÿ�̸� ����
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
		// ���� BGM�� ���߰� ���� BGM�� ���
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


		// ���� BGM�� ���� Ÿ�̸� ���� (50�� ��)
		GetWorld()->GetTimerManager().SetTimer(BossMusicTimerHandle, this, &AJY_GameModeBase::PlayBossMusic, BossMusicStartTime, false);
		// �÷��̾� ĳ���͸� ã�� HUD�� ����
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

