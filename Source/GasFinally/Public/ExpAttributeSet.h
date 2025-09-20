// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "ExpAttributeSet.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLevelChanged, float, OldExpLevel, float, NewExpLevel);
UCLASS()
class GASFINALLY_API UExpAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UExpAttributeSet();
	ATTRIBUTE_ACCESSORS_BASIC(UExpAttributeSet, ExpGained);
	ATTRIBUTE_ACCESSORS_BASIC(UExpAttributeSet, MaxExpGained);
	ATTRIBUTE_ACCESSORS_BASIC(UExpAttributeSet, ExpLevel);
	ATTRIBUTE_ACCESSORS_BASIC(UExpAttributeSet, MaxExpLevel);
	ATTRIBUTE_ACCESSORS_BASIC(UExpAttributeSet, DropExp);

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(BlueprintAssignable)
	mutable FLevelChanged OnLevelChanged;


protected:
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")	
	FGameplayAttributeData ExpGained;

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxExpGained;
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData ExpLevel;

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxExpLevel;

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData DropExp;
};
