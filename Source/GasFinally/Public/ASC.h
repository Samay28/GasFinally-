

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "ASC.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GASFINALLY_API UASC : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UASC();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};
