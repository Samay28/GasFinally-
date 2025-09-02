

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include <GameplayEffect.h>
#include "ItemTypes.generated.h"


USTRUCT(BlueprintType)
struct FConsumableProps
{	
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> ItemEffectClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ItemEffectLevel;


};

USTRUCT(BlueprintType)
struct FMasterItemDefinition : public FTableRowBase //used to make data tables 
{
	                                                                                
	GENERATED_BODY()


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag ItemTag;

	UPROPERTY(BlueprintReadOnly)
	int32 Quantity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText ItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UTexture2D> ItemIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText ItemDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FConsumableProps ConsumableProps;
};