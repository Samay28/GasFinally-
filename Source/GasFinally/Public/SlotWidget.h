// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include <Components/Image.h>
#include "SlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class GASFINALLY_API USlotWidget : public UUserWidget
{
    GENERATED_BODY()

public:

    UPROPERTY(EditDefaultsOnly)
    UImage* ItemIcon;

    UPROPERTY(EditDefaultsOnly)
    UTextBlock* QuantityText;

    //UPROPERTY(EditAnywhere)
    //USlotWidget* NextSlot;

    UPROPERTY(EditAnywhere)
    bool bIsOccupied;

    // This should NOT be BPImplementableEvent, just BlueprintCallable
    UFUNCTION(BlueprintCallable)
    void SetItemIcon(UTexture2D* NewIcon);

    UFUNCTION(BlueprintCallable)
    void setItemIconImage(UImage* img);

    UFUNCTION(BlueprintCallable)
	void setQuantityTextBlock(UTextBlock* txt);
};

