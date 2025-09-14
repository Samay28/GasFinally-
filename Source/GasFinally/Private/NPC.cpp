
#include "NPC.h"
#include "AbilitySystemComponent.h"

ANPC::ANPC()
{

}

void ANPC::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}
