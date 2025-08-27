
#include "InventoryComponent.h"
#include "GameplayTagContainer.h"


UInventoryComponent::UInventoryComponent()
{

	PrimaryComponentTick.bCanEverTick = false;
	
}

void UInventoryComponent::AddItem(const FGameplayTag& ItemTag, int32 Count)
{
	AActor* Owner = GetOwner();
	if(!Owner)
	{
		UE_LOG(LogTemp, Warning, TEXT("InventoryComponent: Owner is null"));
		return;
	}


	//if it was an online game, here we would check if the server is authoritative 
	// if(!owner->HasAuthority()) ServerRPC(); 

	//further code from here will only be executed if server calls this 

	if(InventoryMap.Contains(ItemTag))
	{
		InventoryMap[ItemTag] += Count;
	}
	else
	{
		InventoryMap.Add(ItemTag, Count);
	}

	UE_LOG(LogTemp, Warning, TEXT("InventoryComponent: Added %d of item %s. Total now: %d"), Count, *ItemTag.ToString(), InventoryMap[ItemTag]);
}

//server rpc example
//it will call AddItem on the server allowing client to make the changes 


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

}


