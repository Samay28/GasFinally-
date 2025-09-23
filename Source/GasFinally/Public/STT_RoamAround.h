// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "STT_RoamAround.generated.h"

/**
 * 
 */
UCLASS()
class GASFINALLY_API USTT_RoamAround : public UStateTreeTaskBlueprintBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Context")
	TObjectPtr<class AGasFinallyCharacter> NPC;
	
};
