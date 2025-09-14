// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "TA_SphereTrace.generated.h"

/**
 * 
 */
UCLASS()
class GASFINALLY_API ATA_SphereTrace : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()
public:
	ATA_SphereTrace();

	virtual void StartTargeting(UGameplayAbility* Ability) override;
	virtual void ConfirmTargeting() override;

protected:

	UFUNCTION(BlueprintImplementableEvent)
	FHitResult GetSphereHitResult(AActor* InSourceActor);
	
};
