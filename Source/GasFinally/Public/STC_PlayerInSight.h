// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeConditionBlueprintBase.h"
#include "STC_PlayerInSight.generated.h"

/**
 * 
 */
UCLASS()
class GASFINALLY_API USTC_PlayerInSight : public UStateTreeConditionBlueprintBase
{
	GENERATED_BODY()

public:

	USTC_PlayerInSight(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, Category = "Context")
	TObjectPtr<class ANPC> NPCContext;
	
	UPROPERTY(EditAnywhere, Category = "Target")
	TObjectPtr<class ACharacter> TargetContext;

protected:

	virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;

};
