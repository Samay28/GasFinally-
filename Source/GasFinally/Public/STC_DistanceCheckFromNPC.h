// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeConditionBlueprintBase.h"
#include "STC_DistanceCheckFromNPC.generated.h"

/**
 * 
 */
UCLASS()
class GASFINALLY_API USTC_DistanceCheckFromNPC : public UStateTreeConditionBlueprintBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Distance")
	float DistanceThreshold = 50.f;

	UPROPERTY(EditAnywhere, Category = "Context")
	TObjectPtr<class ANPC> OwnerNPC;

	UPROPERTY(EditAnywhere, Category = "Condition")
	TObjectPtr<AActor> TargetActor = nullptr;

	UPROPERTY(EditAnywhere, Category = "Condition")
	bool bLessOrEqual = true;

protected:
	virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;

	
};
