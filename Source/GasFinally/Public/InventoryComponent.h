// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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

protected:

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAcess = "true"))
	TMap<FGameplayTag, int32> InventoryMap;

private:


		
};
