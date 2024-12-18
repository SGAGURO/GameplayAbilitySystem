#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CBot.generated.h"

class UPawnSensingComponent;
class UCAttributeComponent;

UCLASS()
class GAS_API ACBot : public ACharacter
{
	GENERATED_BODY()

public:
	ACBot();

protected:
	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent* PawnSensingComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCAttributeComponent* AttributeComp;
};
