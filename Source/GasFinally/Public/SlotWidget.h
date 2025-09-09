// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include <Components/Image.h>
#include <GameplayTagContainer.h>
#include "SlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class GASFINALLY_API USlotWidget : public UUserWidget
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UImage* ItemIcon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UTextBlock* QuantityText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag ItemTagWidget;

    UPROPERTY(EditAnywhere)
    bool bIsOccupied;


	USlotWidget* nextSlot;

    UFUNCTION(BlueprintCallable)
    void SetItemIcon(UTexture2D* NewIcon);

    UFUNCTION(BlueprintCallable)
    void setItemIconImage(UImage* img);

    UFUNCTION(BlueprintCallable)
	void setQuantityTextBlock(UTextBlock* txt);
};

