#pragma once

#include "CoreMinimal.h"
#include "Interact/CPickUpBase.h"
#include "CCredit.generated.h"

UCLASS()
class GAS_API ACCredit : public ACPickUpBase
{
	GENERATED_BODY()
	
public:
	ACCredit();

public:
	void Interact_Implementation(APawn* InstigatorPawn) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Credits")
	int32 CreditsAmount;

};
