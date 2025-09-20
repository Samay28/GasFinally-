// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <ItemTypes.h>
#include <ItemTypesToTables.h>
#include <MainWidget.h>
#include "InventoryComponent.generated.h"

struct FGameplayTag;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GASFINALLY_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UInventoryComponent();

	UFUNCTION(BlueprintCallable)
	void AddItem(const FGameplayTag& ItemTag, int32 Count = 1);


	UFUNCTION(BlueprintCallable)
	void UseItem(int32 slotNum, int32 Count);


	UFUNCTION(Blueprintpure)
	FMasterItemDefinition GetItemDefinitionByTag(const FGameplayTag ItemTag) const;


	UPROPERTY()
	UMainWidget* MainWidgetInstance;


	UPROPERTY(BlueprintReadWrite)
	int32 ActiveSlotNumber = 1; // 1 to 5

	void InitializeWidget(UMainWidget* Widget) { MainWidgetInstance = Widget; }
protected:

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAcess = "true"))  //its never replicated 
	TMap<FGameplayTag, int32> InventoryMap;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAcess = "true"))
	TMap<int, FGameplayTag> SlotToTagMap; // which slot has which tag

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UItemTypesToTables> InventoryDefinitions;

private:

	IInventoryInterface* GetInventoryInterface() const;
		
};
