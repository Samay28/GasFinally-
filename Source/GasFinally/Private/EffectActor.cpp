
#include "EffectActor.h"
#include "Components/BoxComponent.h"
#include <AbilitySystemComponent.h>
#include <AbilitySystemBlueprintLibrary.h>

AEffectActor::AEffectActor()
{
 
	PrimaryActorTick.bCanEverTick = false;

	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>("ActorMesh");
	SetRootComponent(ActorMesh);

	OverlapBox = CreateDefaultSubobject<UBoxComponent>("Box comp");
	OverlapBox->SetupAttachment(GetRootComponent());
	OverlapBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

}


void AEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
	OverlapBox->OnComponentBeginOverlap.AddDynamic(this, &AEffectActor::OverlapBegin);
}

void AEffectActor::OverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(UAbilitySystemComponent* otherASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
	{
		
			FGameplayEffectContextHandle EffectContext = otherASC->MakeEffectContext();
			EffectContext.AddSourceObject(this);
			FGameplayEffectSpecHandle SpecHandle = otherASC->MakeOutgoingSpec(OverlapEffect, 1, EffectContext);
			if(SpecHandle.IsValid())
			{
				otherASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
			}
			
			Destroy();
	}
}



