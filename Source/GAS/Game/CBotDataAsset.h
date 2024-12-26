#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CBotDataAsset.generated.h"

class UCAction;

UCLASS()
class GAS_API UCBotDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawn")
	TSubclassOf<AActor> BotClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawn")
	TArray<TSubclassOf<UCAction>> Actions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	UTexture2D* Icon;
	
	FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("CBot", GetFName());
	}
};
