#pragma once

#include "CoreMinimal.h"
#include "Actions/CAction.h"
#include "CAction_Projectile.generated.h"

UCLASS()
class GAS_API UCAction_Projectile : public UCAction
{
	GENERATED_BODY()

public:
	UCAction_Projectile();

public:
	virtual void StartAction_Implementation(AActor* Instigator);

protected:
	UFUNCTION()
	void AttackDelay_Elapsed(ACharacter* InstigatorCharacter);

protected:
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	FName HandSocketName;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	float AttackAnimDelay;

	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;

	UPROPERTY(EditAnywhere, Category = "Attack")
	UParticleSystem* CastingEffect;
	
};
