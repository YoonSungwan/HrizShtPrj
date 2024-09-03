// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverUI.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UGameOverUI::NativeConstruct()
{
	Super::NativeConstruct();

	// 각 버튼 입력 이벤트에 대응하는 함수를 연결한다.
	Restart->OnClicked.AddDynamic(this, &UGameOverUI::RestartGame);
	Quit->OnClicked.AddDynamic(this, &UGameOverUI::QuitGame);
}

void UGameOverUI::RestartGame()
{
	// 레벨을 다시 로드한다.
	UGameplayStatics::OpenLevel(GetWorld(), "MainLv");
}

void UGameOverUI::QuitGame()
{

	// 현재 실행 중인 월드 오브젝트를 가져온다.
	UWorld* currentWorld = GetWorld();

	// 앱을 종료시킨다.
	UKismetSystemLibrary::QuitGame(currentWorld, currentWorld->GetFirstPlayerController(), EQuitPreference::Quit, false);
}