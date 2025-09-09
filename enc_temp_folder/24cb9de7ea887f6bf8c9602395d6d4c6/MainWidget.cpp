

#include "MainWidget.h"
#include "SlotWidget.h"
#include "ItemTypes.h"
#include <GameplayTagContainer.h>
//#include "Blueprint/WidgetTree.h"
#include <Components/HorizontalBox.h>
#include <MyAbilitySystemLibrary.h>

void UMainWidget::AddItemToWidget(const FGameplayTag ItemTag, const int Quantity)
{
	// Start with slot 1 if ActiveSlot isn’t already set
	if (!ActiveSlot)
	{
		ActiveSlot = Slot1;
	}

	if (!ActiveSlot)
	{
		UE_LOG(LogTemp, Warning, TEXT("Active slot is NULL"));
		return;
	}

	// CASE 1: Slot already occupied with the SAME item -> stack quantity
	if (ActiveSlot->bIsOccupied && ActiveSlot->ItemTagWidget == ItemTag)
	{
		int CurrentQuantity = FCString::Atoi(*ActiveSlot->QuantityText->GetText().ToString());
		CurrentQuantity += Quantity;
		ActiveSlot->QuantityText->SetText(FText::AsNumber(CurrentQuantity));
		return;
	}

	// CASE 2: Slot is occupied but with a DIFFERENT item -> move to next slot
	if (ActiveSlot->bIsOccupied && ActiveSlot->ItemTagWidget != ItemTag)
	{
		if (ActiveSlot->nextSlot)
		{
			ActiveSlot = ActiveSlot->nextSlot;
			AddItemToWidget(ItemTag, Quantity);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No empty slot available for item %s"), *ItemTag.ToString());
		}
		return;
	}

	// CASE 3: Slot is empty -> assign new item
	if (!ActiveSlot->bIsOccupied)
	{
		if (const FMasterItemDefinition* Row = UMyAbilitySystemLibrary::GetDataTableRowByTag<FMasterItemDefinition>(ItemDataTable, ItemTag))
		{
			ActiveSlot->SetItemIcon(Row->ItemIcon);
			ActiveSlot->QuantityText->SetText(FText::AsNumber(Quantity));
			ActiveSlot->bIsOccupied = true;
			ActiveSlot->ItemTagWidget = ItemTag;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Could not find row for tag %s in ItemDataTable"), *ItemTag.ToString());
		}
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




 
