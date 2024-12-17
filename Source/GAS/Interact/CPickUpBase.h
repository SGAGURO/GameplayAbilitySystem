#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/CGameplayInterface.h"
#include "CPickUpBase.generated.h"

class USphereComponent;

UCLASS()
class GAS_API ACPickUpBase : public AActor, public ICGameplayInterface
{
	GENERATED_BODY()
	
public:	
	ACPickUpBase();

public:
	void Interact_Implementation(APawn* InstigatorPawn) override;

protected:
protected:
	UFUNCTION()
	void Show();

	void HideAndCooldown();
	void SetState(bool bActive);

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* SphereComp;

	UPROPERTY(EditAnywhere, Category = "PickUp")
	float RespawnTime;

	FTimerHandle TimerHandle_RespawnTimer;
};
