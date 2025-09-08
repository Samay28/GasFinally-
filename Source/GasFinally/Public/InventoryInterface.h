// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include <GameplayTagContainer.h>
#include "InventoryInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInventoryInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GASFINALLY_API IInventoryInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void AddItemToWidget(const FGameplayTag ItemTag, const int Quantity) = 0;
	virtual void UseItemFromWidget(const int Quantity) = 0;
	virtual void RemoveItemFromWidget() = 0;
};
