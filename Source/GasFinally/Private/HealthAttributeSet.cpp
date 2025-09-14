#include "HealthAttributeSet.h"
#include "GameplayEffectExtension.h"


UHealthAttributeSet::UHealthAttributeSet()
{
	InitHealth(100.0f);
	InitMaxHealth(100.0f);
}

void UHealthAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		const float DamageValue = GetDamage();
		const float OldHealthValue = GetHealth();
		const float MaxHealthValue = GetMaxHealth();
		const float NewHealthValue = FMath::Clamp(OldHealthValue - DamageValue, 0.0f, MaxHealthValue);
		
		if(OldHealthValue != NewHealthValue)
		{
			SetHealth(NewHealthValue);
		}
		SetDamage(0.0f);
	}
	else if (Data.EvaluatedData.Attribute == GetHealAttribute())
	{
		const float HealValue = GetHeal();
		const float OldHealthValue = GetHealth();
		const float MaxHealthValue = GetMaxHealth();
		const float NewHealthValue = FMath::Clamp(OldHealthValue + HealValue, 0.0f, MaxHealthValue);

		if (OldHealthValue != NewHealthValue)
		{
			SetHealth(NewHealthValue);
		}
		SetHeal(0.0f);
	}
}

void UHealthAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)// we clamp here
{
	UE_LOG(LogTemp, Warning, TEXT("PreChange: Attribute '%s'"), *Attribute.AttributeName);
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
	Super::PreAttributeBaseChange(Attribute, NewValue);
}

void UHealthAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) //notify listeners after the attribute has changed(UI, etc.)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		OnHealthChanged.Broadcast(this, OldValue, NewValue);
	}
	else if (Attribute == GetMaxHealthAttribute())
	{
		const float CurrHealth = GetHealth();
		OnHealthChanged.Broadcast(this, CurrHealth, CurrHealth);
	}

}
