// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GI_PlayerGame.generated.h"

/**
 * 
 */
UCLASS()
class HRIZSHTPRJ_API UGI_PlayerGame : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SelectedIndex = 0;
};
