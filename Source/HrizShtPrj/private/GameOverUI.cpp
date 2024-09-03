// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverUI.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UGameOverUI::NativeConstruct()
{
	Super::NativeConstruct();

	// �� ��ư �Է� �̺�Ʈ�� �����ϴ� �Լ��� �����Ѵ�.
	Restart->OnClicked.AddDynamic(this, &UGameOverUI::RestartGame);
	Quit->OnClicked.AddDynamic(this, &UGameOverUI::QuitGame);
}

void UGameOverUI::RestartGame()
{
	// ������ �ٽ� �ε��Ѵ�.
	UGameplayStatics::OpenLevel(GetWorld(), "MainLv");
}

void UGameOverUI::QuitGame()
{

	// ���� ���� ���� ���� ������Ʈ�� �����´�.
	UWorld* currentWorld = GetWorld();

	// ���� �����Ų��.
	UKismetSystemLibrary::QuitGame(currentWorld, currentWorld->GetFirstPlayerController(), EQuitPreference::Quit, false);
}