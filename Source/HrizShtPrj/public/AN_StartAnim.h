// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_StartAnim.generated.h"

/**
 * 
 */
UCLASS()
class HRIZSHTPRJ_API UAN_StartAnim : public UAnimNotify
{
	GENERATED_BODY()
	
public :

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

};
