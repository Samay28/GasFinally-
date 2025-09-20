// Fill out your copyright notice in the Description page of Project Settings.


#include "ExpAttributeSet.h"
#include "GameplayEffectExtension.h"

UExpAttributeSet::UExpAttributeSet() : MaxExpGained(9990.f), MaxExpLevel(1000.f)
{
	InitExpLevel(1.f);
	InitDropExp(0.f);
	InitExpGained(0.f);
}

void UExpAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	if(Attribute==GetExpLevelAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxExpLevel());
		NewValue = FMath::TruncToFloat(NewValue);
	}
	else if(Attribute == GetExpGainedAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxExpGained());
	}
	
}

void UExpAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Attribute == GetExpGainedAttribute())
	{
		float OldExpLevel = GetExpLevel();
		float NewExpLevel = FMath::TruncToFloat(GetExpGained() / 10.f) + 1.f;
		if(NewExpLevel > OldExpLevel)
		{
			SetExpLevel(NewExpLevel);
			OnLevelChanged.Broadcast(OldExpLevel, NewExpLevel);
		}
	}
}
