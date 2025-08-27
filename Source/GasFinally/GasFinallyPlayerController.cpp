// Copyright Epic Games, Inc. All Rights Reserved.


#include "GasFinallyPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InventoryComponent.h"
#include "InputMappingContext.h"
#include <AbilitySystemBlueprintLibrary.h>

void AGasFinallyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Add Input Mapping Contexts
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
		{
			Subsystem->AddMappingContext(CurrentContext, 0);
		}
	}
}

UAbilitySystemComponent* AGasFinallyPlayerController::GetAbilitySystemComponent() const
{
	return UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn());
}

AGasFinallyPlayerController::AGasFinallyPlayerController()
{
	InventoryComp = CreateDefaultSubobject<UInventoryComponent>("InventoryComp");
}
