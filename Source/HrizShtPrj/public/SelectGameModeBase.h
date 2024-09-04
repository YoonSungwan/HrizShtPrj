// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SelectGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class HRIZSHTPRJ_API ASelectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void FindCamera();

	UFUNCTION(BlueprintCallable)
	void SetFocusIndex(bool bIncrease);

	UFUNCTION(BlueprintCallable)
	void UpdateTargetLocation();

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class USelectUI> SubUI;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class AActor* CameraActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector StartPosition = {0.f, 0.f, 0.f};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector TargetPosition = {0.f, 200.f, 0.f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<class AParentPlayer*> players;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 CurrentFocusIndex = 0;
private:
	class USelectUI* selectUI;

};
