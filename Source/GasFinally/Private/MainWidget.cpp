

#include "MainWidget.h"
#include "SlotWidget.h"
#include "ItemTypes.h"
#include <GameplayTagContainer.h>
#include <Components/HorizontalBox.h>
#include <MyAbilitySystemLibrary.h>

void UMainWidget::AddItemToWidget(const FGameplayTag ItemTag, const int Quantity)
{
	USlotWidget* CurrSlot = Slot1;
	int32 SlotIndex = 1;

	while (CurrSlot)
	{
		// CASE 1: Slot has same item → stack
		if (CurrSlot->bIsOccupied && CurrSlot->ItemTagWidget == ItemTag)
		{
			int CurrentQuantity = FCString::Atoi(*CurrSlot->QuantityText->GetText().ToString());
			CurrentQuantity += Quantity;
			CurrSlot->QuantityText->SetText(FText::AsNumber(CurrentQuantity));
			numNew = SlotIndex; // store the correct slot number
			return;
		}

		// CASE 2: Slot is empty → assign new item
		if (!CurrSlot->bIsOccupied)
		{
			if (const FMasterItemDefinition* Row = UMyAbilitySystemLibrary::GetDataTableRowByTag<FMasterItemDefinition>(ItemDataTable, ItemTag))
			{
				CurrSlot->SetItemIcon(Row->ItemIcon);
				CurrSlot->QuantityText->SetText(FText::AsNumber(Quantity));
				CurrSlot->bIsOccupied = true;
				CurrSlot->ItemTagWidget = ItemTag;

				numNew = SlotIndex; // store the correct slot number
				return;
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Could not find row for tag %s in ItemDataTable"), *ItemTag.ToString());
				return;
			}
		}

		// Otherwise, move to next slot
		CurrSlot = CurrSlot->nextSlot;
		SlotIndex++;
	}

	UE_LOG(LogTemp, Warning, TEXT("No empty slot available for item %s"), *ItemTag.ToString());
}



void UMainWidget::UseItemFromWidget(int32 SlotNum,const int Quantity)
{	
	SetActiveSlot(SlotNum);
	if (ActiveSlot)
	{
		ActiveSlot->QuantityText->SetText(FText::AsNumber(Quantity));
	}
}

void UMainWidget::RemoveItemFromWidget(int slotNum)
{	
	SetActiveSlot(slotNum);
	if (ActiveSlot)
	{
		ActiveSlot->ItemIcon->SetBrushFromTexture(nullptr);
		ActiveSlot->QuantityText->SetText(FText::FromString(" "));
		ActiveSlot->bIsOccupied = false;
	}
}

int32 UMainWidget::GetSlotNumber() const
{
	return numNew;
}

//void UMainWidget::SetSlotNumber(int32 num)
//{
//	numNew = num;
//}

void UMainWidget::SetActiveSlot(int32 slotNum)
{	
	ActiveSlot = Slot1;
	while (slotNum - 1 > 0)
	{
		if (ActiveSlot->nextSlot)
		{
			ActiveSlot = ActiveSlot->nextSlot;
			slotNum--;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No such slot number %d"), slotNum);
			return;
		}
	}
}


//USlotWidget* UMainWidget::GetEmptySlot()
//{	
//	USlotWidget* CurrentSlot = Slot1;
//	int count = 1;
//	while (CurrentSlot)
//	{	
//		if (!CurrentSlot->bIsOccupied)
//		{	
//			UE_LOG(LogTemp, Warning, TEXT("Slot free = %d"), count);
//			SetSlotNumber(count);
//			return CurrentSlot; // found a free slot
//		}
//		count++;
//		CurrentSlot = CurrentSlot->nextSlot;
//	}
//	return nullptr;
//}

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




 
