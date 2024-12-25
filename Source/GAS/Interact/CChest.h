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

public:
	void Interact_Implementation(APawn* InstigatorPawn) override;
	void OnActorLoaded_Implementation() override;

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BottomMesh;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UStaticMeshComponent* TopMesh;

public:
	UPROPERTY(EditAnywhere)
	float TargetPitch;

	UPROPERTY(BlueprintReadOnly, SaveGame, ReplicatedUsing = "OnRep_TopOpened")
	bool bTopOpened;

protected:
	UFUNCTION()
	void OnRep_TopOpened();
};
