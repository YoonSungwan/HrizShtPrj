// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverUI.generated.h"

/**
 * 
 */
UCLASS()
class HRIZSHTPRJ_API UGameOverUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, meta =(BindWidget))
	class UButton* Restart;

	UPROPERTY(EditAnywhere, meta =(BindWidget))
	class UButton* Quit;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* Endimage;

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void RestartGame();

	UFUNCTION()
	void QuitGame();
};
