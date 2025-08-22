// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "HealthAttributeSet.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAttributeChangedEvent, UAttributeSet*, AttributeSet, float, OldValue, float, NewValue);
UCLASS()
class GASFINALLY_API UHealthAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

	public:
		UHealthAttributeSet();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGameplayAttributeData MaxHealth;

	ATTRIBUTE_ACCESSORS_BASIC(UHealthAttributeSet, Health);
	ATTRIBUTE_ACCESSORS_BASIC(UHealthAttributeSet, MaxHealth);

	UFUNCTION(BlueprintPure, Category = "Attributes|Health")
	float GetHealthCurrent() const { return Health.GetCurrentValue(); }

	UFUNCTION(BlueprintPure, Category = "Attributes|Health")
	float GetHealthBase() const { return Health.GetBaseValue(); }

	UFUNCTION(BlueprintPure, Category = "Attributes|Health")
	float GetMaxHealthCurrent() const { return MaxHealth.GetCurrentValue(); }

	UFUNCTION(BlueprintPure, Category = "Attributes|Health")
	float GetMaxHealthBase() const { return MaxHealth.GetBaseValue(); }


	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override; // ourt attribute is laways clamped before it gets set
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override; // broadcast after the attribute has changed

	UPROPERTY(BlueprintAssignable)
	FAttributeChangedEvent OnHealthChanged;
};
