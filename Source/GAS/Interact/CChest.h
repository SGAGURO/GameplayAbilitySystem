#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/CGameplayInterface.h"
#include "CChest.generated.h"

UCLASS()
class GAS_API ACChest : public AActor, public ICGameplayInterface
{
	GENERATED_BODY()
	
public:	
	ACChest();

protected:
	virtual void BeginPlay() override;

public:
	void Interact_Implementation(APawn* InstigatorPawn) override;

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BottomMesh;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UStaticMeshComponent* TopMesh;

public:
	UPROPERTY(EditAnywhere)
	float TargetPitch;
};
