#include "NPC.h"
#include "AbilitySystemComponent.h"

ANPC::ANPC()
{

}

void ANPC::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	
}
