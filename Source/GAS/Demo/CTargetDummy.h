#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CTargetDummy.generated.h"

class UCAttributeComponent;

UCLASS()
class GAS_API ACTargetDummy : public AActor
{
	GENERATED_BODY()
	
public:	
	ACTargetDummy();

protected:
	virtual void BeginPlay() override;

protected:
	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UCAttributeComponent* OwningComp, float NewHealth, float Delta);

protected:
	UPROPERTY(VisibleAnywhere)
	UCAttributeComponent* AttributeComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;
};
