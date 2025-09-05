

#include "MainWidget.h"
#include "SlotWidget.h"
#include "ItemTypes.h"
#include <GameplayTagContainer.h>
#include <MyAbilitySystemLibrary.h>

void UMainWidget::AddItemToWidget(const FGameplayTag ItemTag, const int Quantity)
{
	UE_LOG(LogTemp, Warning, TEXT("Adding item to widget: %s, Quantity: %d"), *ItemTag.ToString(), Quantity);
	ActiveSlot = GetEmptySlot();

	//fetch item data from data table using ItemTag here
	if (const FMasterItemDefinition* Row = UMyAbilitySystemLibrary::GetDataTableRowByTag<FMasterItemDefinition>(ItemDataTable, ItemTag))
	{
		// You now have access to icon, name, description, etc
		ActiveSlot->SetItemIcon(Row->ItemIcon);
		ActiveSlot->QuantityText->SetText(FText::AsNumber(Quantity));
		ActiveSlot->bIsOccupied = true;
		UE_LOG(LogTemp, Error, TEXT("Data will be fetched dw samay!"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find row for tag %s in ItemDataTable"), *ItemTag.ToString());
	}
}

//void UMainWidget::InitializeSlots()
//{
//	for(int i=1; i<AllSlots.Num(); i++) ///lllll linked llll list
//	{
//		if(AllSlots.IsValidIndex(i-1) && AllSlots.IsValidIndex(i))
//		{
//			AllSlots[i-1]->NextSlot = AllSlots[i];
//		}
//	}
//}

USlotWidget* UMainWidget::GetEmptySlot()
{
	for (auto const slot : AllSlots)
	{
		if(!slot->bIsOccupied)
		{
			return slot;
		}
	}
	return nullptr;
}


