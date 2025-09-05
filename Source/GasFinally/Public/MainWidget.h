// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryInterface.h"
#include "MainWidget.generated.h"

class USlotWidget;
struct FMasterItemDefinition;
UCLASS()
class GASFINALLY_API UMainWidget : public UUserWidget, public IInventoryInterface
{
	GENERATED_BODY()
	
public:
	void AddItemToWidget(const FGameplayTag ItemTag, const int Quantity) override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	UDataTable* ItemDataTable;


	USlotWidget* ActiveSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class USlotWidget*> AllSlots;

private:
	/*void InitializeSlots();*/
	USlotWidget* GetEmptySlot();

	
};
