// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryInterface.h"
#include "MainWidget.generated.h"

class USlotWidget;
struct FMasterItemDefinition;
class UHorizontalBox;
UCLASS()
class GASFINALLY_API UMainWidget : public UUserWidget, public IInventoryInterface
{
	GENERATED_BODY()
	
public:
	void AddItemToWidget(const FGameplayTag ItemTag, const int Quantity) override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	UDataTable* ItemDataTable;


	UFUNCTION(BlueprintCallable)
	USlotWidget* GetEmptySlot();

	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional), Category = "Inventory")
	USlotWidget* ActiveSlot;

	//UPROPERTY(EditDefaultsOnly)
	//USlotWidget* Slot2;

	//UPROPERTY(EditDefaultsOnly)
	//USlotWidget* Slot3;

	//UPROPERTY(EditDefaultsOnly)
	//USlotWidget* Slot4;

	//UPROPERTY(EditDefaultsOnly)
	//USlotWidget* Slot5;

	


private:
	void InitializeSlots();

	void NativeConstruct() override;

	
};
