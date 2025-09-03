// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "SlotWidget.h"
#include <GameplayTagContainer.h>

void UMainWidget::AddItemToWidget(const FGameplayTag ItemTag, const int Quantity)
{
	UE_LOG(LogTemp, Warning, TEXT("Adding item to widget: %s, Quantity: %d"), *ItemTag.ToString(), Quantity);
}
