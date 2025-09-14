// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "HealthAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAttributeChangedEvent, UAttributeSet*, AttributeSet, float, OldValue, float, NewValue);
UCLASS()
class GASFINALLY_API UHealthAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

	public:
		UHealthAttributeSet();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (HideFromModifiers))
	FGameplayAttributeData Health; //consists of base value and current value

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGameplayAttributeData MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Damage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Heal;



	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, Heal);
	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, Damage);

	UFUNCTION(BlueprintPure, Category = "Attributes|Health")
	float GetHealthCurrent() const { return Health.GetCurrentValue(); }

	UFUNCTION(BlueprintPure, Category = "Attributes|Health")
	float GetMaxHealthCurrent() const { return MaxHealth.GetCurrentValue(); }


	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override; // called after a gameplay effect is applied to this attribute set
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override; // our attribute is laways clamped before it gets set
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override; // broadcast after the attribute has changed

	UPROPERTY(BlueprintAssignable)
	FAttributeChangedEvent OnHealthChanged;
};
