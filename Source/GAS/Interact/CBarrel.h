#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBarrel.generated.h"

class URadialForceComponent;

UCLASS()
class GAS_API ACBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	ACBarrel();

protected:
	virtual void PostInitializeComponents() override;

protected:
	UFUNCTION()
		void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	URadialForceComponent* ForceComp;

};
