#include "STT_AttackPlayer.h"
#include "AbilitySystemComponent.h"
#include "StateTreeExecutionContext.h"
#include "NPC.h" 

USTT_AttackPlayer::USTT_AttackPlayer(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

EStateTreeRunStatus USTT_AttackPlayer::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition)
{
	if (!OwnerNPC)
	{
		return EStateTreeRunStatus::Failed;
	}

	// Get the AbilitySystemComponent from the NPC
	UAbilitySystemComponent* ASC = OwnerNPC->FindComponentByClass<UAbilitySystemComponent>();
	if (!ASC)
	{
		return EStateTreeRunStatus::Failed;
	}

	// Make the tag we want to activate
	FGameplayTagContainer AbilityTags;
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Character.Ability.Attack")));

	// Try to activate ability by tag
	const bool bActivated = ASC->TryActivateAbilitiesByTag(AbilityTags);

	return bActivated ? EStateTreeRunStatus::Succeeded : EStateTreeRunStatus::Failed;
}
