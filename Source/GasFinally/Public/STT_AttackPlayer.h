// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "STT_AttackPlayer.generated.h"

/**
 * 
 */
UCLASS()
class GASFINALLY_API USTT_AttackPlayer : public UStateTreeTaskBlueprintBase
{
	GENERATED_BODY()

public:
	USTT_AttackPlayer(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, Category = "Context")
	TObjectPtr<class ANPC> OwnerNPC;

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context,
		const FStateTreeTransitionResult& Transition) override;
	
};
