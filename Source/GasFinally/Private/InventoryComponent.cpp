
#include "InventoryComponent.h"
#include "MyAbilitySystemLibrary.h"
#include "GameplayTagContainer.h"
#include "AbilitySystemComponent.h" 
#include "InventoryInterface.h"
#include <AbilitySystemBlueprintLibrary.h>


UInventoryComponent::UInventoryComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

}

void UInventoryComponent::AddItem(const FGameplayTag& ItemTag, int32 Count)
{
	AActor* Owner = GetOwner();
	/*UUserWidget* OwnerWidget = Cast<UUserWidget>(Owner);*/
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
		if (MainWidgetClass->GetClass()->ImplementsInterface(UInventoryInterface::StaticClass()))
		{
			IInventoryInterface* InventoryInterface = Cast<IInventoryInterface>(MainWidgetClass->GetClass()->GetDefaultObject());
			if (InventoryInterface)
			{
				InventoryInterface->AddItemToWidget(ItemTag, Count);
			}
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("InventoryComponent: Added %d of item %s. Total now: %d"), Count, *ItemTag.ToString(), InventoryMap[ItemTag]);
}

void UInventoryComponent::UseItem(const FGameplayTag& ItemTag, int32 Count)
{
	AActor* owner = GetOwner();
	if (!owner) return;

	if (!InventoryMap.Contains(ItemTag) || InventoryMap[ItemTag] < Count)
	{
		UE_LOG(LogTemp, Warning, TEXT("InventoryComponent: Tried to use %d of item %s, but not enough in inventory!"), Count, *ItemTag.ToString());
		return;
	}

	const FMasterItemDefinition ItemDef = GetItemDefinitionByTag(ItemTag);
	if (UAbilitySystemComponent* ownerASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(owner)) //grabbed ASC of the owner
	{
		if (IsValid(ItemDef.ConsumableProps.ItemEffectClass))
		{	
			const FGameplayEffectContextHandle EffectContext = ownerASC->MakeEffectContext();
			const FGameplayEffectSpecHandle EffectSpecHandle = ownerASC->MakeOutgoingSpec(ItemDef.ConsumableProps.ItemEffectClass, ItemDef.ConsumableProps.ItemEffectLevel, EffectContext);
			ownerASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

			InventoryMap[ItemTag] -= Count;
			if (InventoryMap[ItemTag] <= 0)
			{
				InventoryMap.Remove(ItemTag);
			}
			UE_LOG(LogTemp, Warning, TEXT("InventoryComponent: Used %d of item %s. Total now: %d"), Count, *ItemTag.ToString(), InventoryMap.Contains(ItemTag) ? InventoryMap[ItemTag] : 0);
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


