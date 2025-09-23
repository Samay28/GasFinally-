// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "STT_FindRandomLocation.generated.h"


UCLASS()
class GASFINALLY_API USTT_FindRandomLocation : public UStateTreeTaskBlueprintBase
{
	GENERATED_BODY()
	
public:


	USTT_FindRandomLocation(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float SearchRadius = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Output")
	FVector OutLocation;

	//to be called when task starts
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context,
		const FStateTreeTransitionResult& Transition) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Context")
	TObjectPtr<class ANPC> NPC;
};
