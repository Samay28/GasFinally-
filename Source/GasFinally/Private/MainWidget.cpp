

#include "MainWidget.h"
#include "SlotWidget.h"
#include "ItemTypes.h"
#include <GameplayTagContainer.h>
//#include "Blueprint/WidgetTree.h"
#include <Components/HorizontalBox.h>
#include <MyAbilitySystemLibrary.h>

void UMainWidget::AddItemToWidget(const FGameplayTag ItemTag, const int Quantity)
{	
	
	ActiveSlot = GetEmptySlot();
	if (!ActiveSlot)
	{
		UE_LOG(LogTemp, Warning, TEXT("Active slot NULL"));
		return;
	}

	//fetch item data from data table using ItemTag here
	if (const FMasterItemDefinition* Row = UMyAbilitySystemLibrary::GetDataTableRowByTag<FMasterItemDefinition>(ItemDataTable, ItemTag))
	{
		ActiveSlot->SetItemIcon(Row->ItemIcon);
		ActiveSlot->QuantityText->SetText(FText::AsNumber(Quantity));
		ActiveSlot->bIsOccupied = true;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find row for tag %s in ItemDataTable"), *ItemTag.ToString());
	}
}

void UMainWidget::UseItemFromWidget(const int Quantity)
{
	ActiveSlot = Slot1;
	ActiveSlot->QuantityText->SetText(FText::AsNumber(Quantity));
}

void UMainWidget::RemoveItemFromWidget()
{
	if (ActiveSlot)
	{
		ActiveSlot->ItemIcon->SetBrushFromTexture(nullptr);
		ActiveSlot->QuantityText->SetText(FText::FromString(" "));
		ActiveSlot->bIsOccupied = false;
	}
}


USlotWidget* UMainWidget::GetEmptySlot()
{	
	USlotWidget* CurrentSlot = Slot1;
	while (CurrentSlot)
	{
		if (!CurrentSlot->bIsOccupied)
		{	
			UE_LOG(LogTemp, Warning, TEXT("Slot free = %s"), *CurrentSlot->GetName());
			return CurrentSlot; // found a free slot
		}

		CurrentSlot = CurrentSlot->nextSlot;
	}
	return nullptr;
}

void UMainWidget::InitializeSlots()
{
	Slot1->nextSlot = Slot2;
	Slot2->nextSlot = Slot3;
	Slot3->nextSlot = Slot4;
	Slot4->nextSlot = Slot5;
	Slot5->nextSlot = nullptr;
}

void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeSlots();

	// Debug check
	//USlotWidget* Curr = Slot1;
	//int i = 1;
	//while (Curr)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Slot%d = %s"), i++, *Curr->GetName());
	//	Curr = Curr->nextSlot;
	//}
}




 
