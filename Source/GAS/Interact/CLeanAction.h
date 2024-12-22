#pragma once

#include "CoreMinimal.h"
#include "Interact/CPickUpBase.h"
#include "CLeanAction.generated.h"

class UCAction;

UCLASS()
class GAS_API ACLeanAction : public ACPickUpBase
{
	GENERATED_BODY()

public:
	void Interact_Implementation(APawn* InstigatorPawn) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Action")
	TSubclassOf<UCAction> ActionToLearn;
};
