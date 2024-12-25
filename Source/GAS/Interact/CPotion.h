#pragma once

#include "CoreMinimal.h"
#include "Interact/CPickUpBase.h"
#include "CPotion.generated.h"

UCLASS()
class GAS_API ACPotion : public ACPickUpBase
{
	GENERATED_BODY()

public:
	ACPotion();
	
public:
	void Interact_Implementation(APawn* InstigatorPawn) override;

	FText GetInteractText_Implementation(APawn* InstigatorPawn) override;

protected:
	UPROPERTY(EditAnywhere, Category = "HealthPotion")
	int32 CreditCost;
};
