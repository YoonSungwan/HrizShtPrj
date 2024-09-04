// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectGameModeBase.h"
#include "SelectUI.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "ParentPlayer.h"

void ASelectGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (SubUI != nullptr)
	{
		selectUI = CreateWidget<USelectUI>(GetWorld(), SubUI);

		APlayerController* pc = GetWorld()->GetFirstPlayerController();

		if (selectUI != nullptr)
		{
			FInputModeUIOnly;
			selectUI->AddToViewport();
			pc->bShowMouseCursor = true;
			pc->SetInputMode(FInputModeUIOnly());
			FindCamera();

			if (CameraActor != nullptr)
			{
				StartPosition = CameraActor->GetActorLocation();
				TArray<AActor*> FoundPlayers;
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), AParentPlayer::StaticClass(), FoundPlayers);

				players.Empty();
				for (AActor* actor : FoundPlayers)
				{
					AParentPlayer* Player = Cast<AParentPlayer>(actor);
					if (Player != nullptr)
					{
						players.Emplace(Player);
					}
				}
			}
		}
	}
}

void ASelectGameModeBase::FindCamera()
{
	if (GetWorld() != nullptr)
	{
		// 카메라 Actor 찾기
		ACameraActor* FoundCamera = Cast<ACameraActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ACameraActor::StaticClass()));
	
		// 카메라 찾기, CameraActor 세팅
		if (FoundCamera != nullptr)
		{
			CameraActor = FoundCamera;
		}
	}
}

void ASelectGameModeBase::SetFocusIndex(bool bIncrease)
{
	int32 PlayersCount = players.Num();
	if (bIncrease)
	{
		++CurrentFocusIndex;
		if (CurrentFocusIndex >= PlayersCount)
		{
			CurrentFocusIndex = 0;
		}
	}

	else if (bIncrease == false)
	{
		--CurrentFocusIndex;
		if (CurrentFocusIndex < 0)
		{
			CurrentFocusIndex = (PlayersCount - 1);
		}
	}
}

void ASelectGameModeBase::UpdateTargetLocation()
{
	TargetPosition = players[CurrentFocusIndex]->GetActorLocation() + FVector(0.f, 50.f, 0.f);
}
