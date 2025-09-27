#include "STC_PlayerInSight.h"
#include "StateTreeExecutionContext.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "NPC.h"

USTC_PlayerInSight::USTC_PlayerInSight(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool USTC_PlayerInSight::TestCondition(FStateTreeExecutionContext& Context) const
{
	UWorld* World = Context.GetWorld();
	if (!World || !NPCContext || !TargetContext)
	{
		return false; // invalid context
	}

	FVector Start = NPCContext->GetActorLocation();
	FVector End = TargetContext->GetActorLocation();
	FHitResult Hit;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(NPCContext);

	// Do line of sight trace
	bool bHit = World->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params);

	// Visible if nothing blocks OR the thing hit is the target
	return (bHit || Hit.GetActor() != TargetContext);
}
