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
        return true; // treat as "not in sight" if invalid
    }

    FVector Start = NPCContext->GetActorLocation();
    FVector End = TargetContext->GetActorLocation();
    FHitResult Hit;

    FCollisionQueryParams Params;
    Params.AddIgnoredActor(NPCContext);

    bool bHit = World->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params);

    // Case 1: nothing hit → target is visible (not blocked)
    if (!bHit)
    {
        return false; // player IS in sight → condition fails
    }

    // Case 2: hit something, check if it's the player
    if (Hit.GetActor() == TargetContext)
    {
        return false; // player IS in sight → condition fails
    }

    // Case 3: hit something else
    return true; // player is blocked → condition succeeds (not in sight)
}

