#pragma once

#include "CoreMinimal.h"
#include "Actions/CActionEffect.h"
#include "CActionEffect_Thorns.generated.h"

UCLASS()
class GAS_API UCActionEffect_Thorns : public UCActionEffect
{
	GENERATED_BODY()
	
public:
	UCActionEffect_Thorns();

public:
	void StartAction_Implementation(AActor* Instigator) override;
	void StopAction_Implementation(AActor* Instigator) override;

protected:
	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UCAttributeComponent* OwningComp, float NewHealth, float Delta);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Thorns")
	float ReflectFraction;
};
