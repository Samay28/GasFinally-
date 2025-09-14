// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GasFinallyCharacter.h"
#include "NPC.generated.h"

/**
 * 
 */
UCLASS()
class GASFINALLY_API ANPC : public AGasFinallyCharacter
{
	GENERATED_BODY()
public:
	ANPC();
	virtual void PossessedBy(AController* NewController) override;

	
};
