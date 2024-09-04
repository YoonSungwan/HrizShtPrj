// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "ParentPlayer.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "GameFramework/PlayerController.h"
#include "JY_GameModeBase.h"
#include "PlayerStruct.h"
#include "Engine/DataTable.h"

void UPlayerHUD::UpdateHealth(int32 Lives)
{
	// 모든 하트를 숨김
	if (Heart1 != nullptr)
	{
		Heart1->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (Heart2 != nullptr)
	{
		Heart2->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (Heart3 != nullptr)
	{
		Heart3->SetVisibility(ESlateVisibility::Collapsed);
	}

	// 생명 수에 따라 하트를 표시
	if (Lives >= 1 && Heart1 != nullptr)
		Heart1->SetVisibility(ESlateVisibility::Visible);

	if (Lives >= 2 && Heart2 != nullptr)
		Heart2->SetVisibility(ESlateVisibility::Visible);

	if (Lives >= 3 && Heart3 != nullptr)
		Heart3->SetVisibility(ESlateVisibility::Visible);
}

void UPlayerHUD::UpdateStopWatch(float Time)
{
	if (stopWatchText)
	{
		int32 Minutes = FMath::FloorToInt(Time / 60.0f);
		int32 Seconds = FMath::FloorToInt(Time) % 60;

		// FString::Printf로 숫자를 2자리로 포맷
		FString TimeString = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
		stopWatchText->SetText(FText::FromString(TimeString));
	}
}

void UPlayerHUD::UpdateJSkillCoolDown(float Ratio)
{
	if (JSkillCooldownBar != nullptr)
	{
		JSkillCooldownBar->SetPercent(Ratio);
	}
}

void UPlayerHUD::UpdateKSkillCoolDown(float Ratio)
{
	if (KSkillCooldownBar != nullptr)
	{
		KSkillCooldownBar->SetPercent(Ratio);
	}
}

void UPlayerHUD::UpdateLSkillCoolDown(float Ratio)
{
	if (LSkillCooldownBar != nullptr)
	{
		LSkillCooldownBar->SetPercent(Ratio);
	}
}

void UPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();
	
// HUD가 초기화될 때 스킬 바 이미지를 업데이트
	
	if (DT_PlayerSelect != nullptr)
	{
		// 플레이어 캐릭터 가져오기
		APlayerController* playerController = GetWorld()->GetFirstPlayerController();
		AParentPlayer* player = Cast<AParentPlayer>(playerController->GetPawn());
		if (playerController != nullptr)
		{
			if (player != nullptr)
			{
				UpdateSkillImages();
			}
		}
		
	}
}

void UPlayerHUD::UpdateSkillImages()
{
	// 플레이어 타입 가져오기
	APlayerController* pc = GetWorld()->GetFirstPlayerController();
	AParentPlayer* player = Cast<AParentPlayer>(pc->GetPawn());

	if (player != nullptr && DT_PlayerSelect != nullptr)
	{
		// 로그를 추가하여 함수 호출 확인
		FString playerType = player->GetPlayerType();	// 플레이어 클래스에서 타입을 가져온다.


		// 데이터 테이블에서 해당플레이어 타입의 데이터를 가져옵니다.
		static const FString ContextString(TEXT("Player Data Context"));
		FPlayerStruct* playerData = DT_PlayerSelect->FindRow<FPlayerStruct>(FName(*playerType), TEXT(""));

		if (playerData != nullptr)
		{
			if (JSkillImg != nullptr && playerData->JSkill)
			{
				JSkillImg->SetBrushFromTexture(playerData->JSkill);
			}

			if (KSkillImg != nullptr && playerData->KSkill)
			{
				KSkillImg->SetBrushFromTexture(playerData->KSkill);
			}

			if (LSkillImg != nullptr && playerData->LSkill)
			{
				LSkillImg->SetBrushFromTexture(playerData->LSkill);
			}
		}
	}
}
