#include "Abilities/GameplayAbility.h"
#include "TA_SphereTrace.h"

ATA_SphereTrace::ATA_SphereTrace()
{
}

void ATA_SphereTrace::StartTargeting(UGameplayAbility* Ability)
{
	Super::StartTargeting(Ability); //used to call the parent class function first
	SourceActor = Ability->GetCurrentActorInfo()->AvatarActor.Get(); //get the actor that owns the ability
	ShouldProduceTargetDataOnServer = true;// for npc to spawn this
}

void ATA_SphereTrace::ConfirmTargeting()
{
	//the parent class function is empty so no need to call it
	check(ShouldProduceTargetData());
	if (IsConfirmTargetingAllowed())
	{	
		FHitResult HitResult = GetSphereHitResult(SourceActor); //call the blueprint function to get the hit result
		FGameplayAbilityTargetDataHandle DataHandle(new FGameplayAbilityTargetData_SingleTargetHit(HitResult)); //create target data handle from hit result
		TargetDataReadyDelegate.Broadcast(DataHandle); //broadcast the target data
	}
}
