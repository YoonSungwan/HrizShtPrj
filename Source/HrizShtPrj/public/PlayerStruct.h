// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "PlayerStruct.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FPlayerStruct : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* JSkill;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* KSkill;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* LSkill;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString playerType;
};
