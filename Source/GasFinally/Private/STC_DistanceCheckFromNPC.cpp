#include "STC_DistanceCheckFromNPC.h"
#include "NPC.h"

bool USTC_DistanceCheckFromNPC::TestCondition(FStateTreeExecutionContext& Context) const
{
	const float Dist = FVector::Dist(OwnerNPC->GetActorLocation(), TargetActor->GetActorLocation());

	if (bLessOrEqual)
	{
		return Dist <= DistanceThreshold;
	}
	else
	{
		return Dist >= DistanceThreshold;
	}
}
