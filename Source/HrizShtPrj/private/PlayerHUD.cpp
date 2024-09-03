// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "ParentPlayer.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "GameFramework/PlayerController.h"

void UPlayerHUD::UpdateHealth(int32 Lives)
{
	// ��� ��Ʈ�� ����
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

	// ���� ���� ���� ��Ʈ�� ǥ��
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

		// FString::Printf�� ���ڸ� 2�ڸ��� ����
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

	// �÷��̾� ĳ���� ��������
	APlayerController* playerController = GetWorld()->GetFirstPlayerController();
	if (playerController != nullptr)
	{
		PlayerCharacter = Cast<AParentPlayer>(playerController->GetPawn());

		if (PlayerCharacter != nullptr)
		{
			//UpdateKSkillCoolDown();
			//UpdateLSkillCoolDown();
		}
	}
}
