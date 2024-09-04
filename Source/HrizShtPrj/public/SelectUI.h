// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SelectUI.generated.h"

/**
 * 
 */
UCLASS()
class HRIZSHTPRJ_API USelectUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* Left_button;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* Right_button;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* Select_button;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* Back_button;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* GameStart_button;
};
