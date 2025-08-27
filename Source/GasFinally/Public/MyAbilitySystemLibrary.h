// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include <GameplayTagContainer.h>
#include "MyAbilitySystemLibrary.generated.h"

/**
 * 
 */
UCLASS()
class GASFINALLY_API UMyAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	template<typename T>
	static T* GetDataTableRowByTag(UDataTable* DataTable, FGameplayTag Tag);
	
};

template<typename T>
inline T* UMyAbilitySystemLibrary::GetDataTableRowByTag(UDataTable* DataTable, FGameplayTag Tag)  //can throw any data table class and it will return the row with the name of the tag
{
	return DataTable->FindRow<T>(Tag.GetTagName(), FString());
}
