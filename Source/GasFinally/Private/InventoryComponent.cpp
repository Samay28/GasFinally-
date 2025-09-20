
#include "InventoryComponent.h"
#include "MyAbilitySystemLibrary.h"
#include "GameplayTagContainer.h"
#include "AbilitySystemComponent.h" 
#include "InventoryInterface.h"
#include <AbilitySystemBlueprintLibrary.h>
#include <GasFinallyPlayerController.h>


UInventoryComponent::UInventoryComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

}

void UInventoryComponent::AddItem(const FGameplayTag& ItemTag, int32 Count)
{	
	if(InventoryMap.Num() >= 5) //max 5 different items
	{
		UE_LOG(LogTemp, Warning, TEXT("InventoryComponent: Inventory full, cannot add item %s"), *ItemTag.ToString());
		return;
	}
	AActor* Owner = GetOwner();
	if (!Owner)
	{
		UE_LOG(LogTemp, Warning, TEXT("InventoryComponent: Owner is null"));
		return;
	}


	//if it was an online game, here we would check if the server is authoritative 
	// if(!owner->HasAuthority()) ServerRPC(); 

	//further code from here will only be executed if server calls this 

	if (InventoryMap.Contains(ItemTag))
	{
		InventoryMap[ItemTag] += Count;
	}
	else
	{
		InventoryMap.Add(ItemTag, Count);
	}
	if (IInventoryInterface* InventoryInterface = GetInventoryInterface())
	{
		InventoryInterface->AddItemToWidget(ItemTag, Count);
		SlotToTagMap.Add(InventoryInterface->GetSlotNumber(), ItemTag);
		UE_LOG(LogTemp, Warning, TEXT("InventoryComponent: Item %s added to slot %d"), *ItemTag.ToString(), InventoryInterface->GetSlotNumber());
	}

	UE_LOG(LogTemp, Warning, TEXT("InventoryComponent: Added %d of item %s. Total now: %d"), Count, *ItemTag.ToString(), InventoryMap[ItemTag]);
}

void UInventoryComponent::UseItem(int32 SlotNum, int32 Count)
{
    AActor* Owner = GetOwner();
    if (!Owner) return;

    // 1. Check if slot exists in SlotToTagMap
    if (!SlotToTagMap.Contains(SlotNum))
    {
        UE_LOG(LogTemp, Warning, TEXT("InventoryComponent: Slot %d does not exist."), SlotNum);
        return;
    }

    const FGameplayTag& ItemTag = SlotToTagMap[SlotNum];

    // 2. Check if slot is empty / invalid
    if (!ItemTag.IsValid() || !InventoryMap.Contains(ItemTag))
    {
        UE_LOG(LogTemp, Warning, TEXT("InventoryComponent: Slot %d is empty."), SlotNum);
        return;
    }

    // 3. Check if enough items exist
    if (InventoryMap[ItemTag] < Count)
    {
        UE_LOG(LogTemp, Warning, TEXT("InventoryComponent: Tried to use %d of item %s, but not enough in inventory!"),
            Count, *ItemTag.ToString());
        return;
    }

    // 4. Get item definition
    const FMasterItemDefinition ItemDef = GetItemDefinitionByTag(ItemTag);
    if (UAbilitySystemComponent* OwnerASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Owner))
    {
        if (IsValid(ItemDef.ConsumableProps.ItemEffectClass))
        {
            const FGameplayEffectContextHandle EffectContext = OwnerASC->MakeEffectContext();
            const FGameplayEffectSpecHandle EffectSpecHandle =
                OwnerASC->MakeOutgoingSpec(ItemDef.ConsumableProps.ItemEffectClass,
                    ItemDef.ConsumableProps.ItemEffectLevel,
                    EffectContext);
            OwnerASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

            InventoryMap[ItemTag] -= Count;

            if (IInventoryInterface* InventoryInterface = GetInventoryInterface())
            {
                InventoryInterface->UseItemFromWidget(SlotNum, Count);
            }

            // 5. Clean up if count drops to 0
            if (InventoryMap[ItemTag] <= 0)
            {
                InventoryMap.Remove(ItemTag);
                SlotToTagMap[SlotNum] = FGameplayTag(); // reset slot to empty

                if (IInventoryInterface* InventoryInterface = GetInventoryInterface())
                {
                    InventoryInterface->RemoveItemFromWidget(SlotNum);
                }
            }

            UE_LOG(LogTemp, Warning, TEXT("InventoryComponent: Used %d of item %s. Total now: %d"),
                Count, *ItemTag.ToString(),
                InventoryMap.Contains(ItemTag) ? InventoryMap[ItemTag] : 0);
        }
    }
}



FMasterItemDefinition UInventoryComponent::GetItemDefinitionByTag(const FGameplayTag ItemTag) const
{
	
	for(const auto & Pair : InventoryDefinitions->TagsToTables)
	{
		if (ItemTag.MatchesTag(Pair.Key)) //does item.counsamble.healthpotion matches with item.consamable? very quick when different items
		{
			return *UMyAbilitySystemLibrary::GetDataTableRowByTag<FMasterItemDefinition>(Pair.Value, ItemTag);
		}
	}

	return FMasterItemDefinition(); //return empty struct if not found
}

//server rpc example
//it will call AddItem on the server allowing client to make the changes 


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

}

IInventoryInterface* UInventoryComponent::GetInventoryInterface() const
{
	if (MainWidgetInstance && MainWidgetInstance->GetClass()->ImplementsInterface(UInventoryInterface::StaticClass()))
	{
		return Cast<IInventoryInterface>(MainWidgetInstance);
	}
	return nullptr;
}


