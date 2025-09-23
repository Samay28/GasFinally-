
#include "STT_FindRandomLocation.h"
#include "NavigationSystem.h"
#include "StateTreeExecutionContext.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

USTT_FindRandomLocation::USTT_FindRandomLocation(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	// Setting a default value for SearchRadius
    SearchRadius = 1000.0f;
	OutLocation = FVector::ZeroVector;
}

EStateTreeRunStatus USTT_FindRandomLocation::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) 
{
    
    if (ACharacter* Player = UGameplayStatics::GetPlayerCharacter(Context.GetWorld(), 0))
    {
        if (UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(Context.GetWorld()))
        {
            FNavLocation Loc;
            if (NavSys->GetRandomPointInNavigableRadius(Player->GetActorLocation(), SearchRadius, Loc))
            {
                FNavLocation ProjectedLoc;
                if (NavSys->ProjectPointToNavigation(Loc.Location, ProjectedLoc))
                {
                    OutLocation = ProjectedLoc.Location;
                    UE_LOG(LogTemp, Warning, TEXT("%s roaming to %s"), *GetNameSafe(this), *OutLocation.ToString());
                    return EStateTreeRunStatus::Succeeded;
                }
            }

        }
    }
    return EStateTreeRunStatus::Failed;
}
