// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "SlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class GASFINALLY_API USlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	UTexture2D* ItemIcon;

	UPROPERTY(EditAnywhere)
	UTextBlock* ItemName;

	UPROPERTY(EditAnywhere)
	USlotWidget* NextSlot;

	UPROPERTY(EditAnywhere)
	int ItemQuantity;

	UPROPERTY(EditAnywhere)
	bool bIsOccupied;
	
};
