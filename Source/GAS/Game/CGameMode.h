#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "Engine/DataTable.h"
#include "CGameMode.generated.h"

class UEnvQuery;
class UCurveFloat;
class UCSaveGame;
class UCBotDataAsset;

USTRUCT(BlueprintType)
struct FBotInfoRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	FBotInfoRow()
	{
		Weight = 1.0f;
		SpawnCost = 5.0f;
		KillReward = 20.0f;
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCBotDataAsset* BotData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Weight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SpawnCost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float KillReward;
};

UCLASS()
class GAS_API ACGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACGameMode();
	
protected:
	void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void StartPlay() override;
	void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

	UFUNCTION(Exec)
	void KillEmAll();

	//Player Dead
public:
	virtual void OnActorKilled(AActor* VictimActor, AActor* Killer);

	UFUNCTION()
	void RespawnPlayerElapsed(AController* Controller);

	//Spawn Bots
protected:
	FTimerHandle TimerHandle_SpawnBots;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float SpawnTimerInterval;

	UFUNCTION()
	void SpawnBotTimerElapsed();

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UEnvQuery* SpawnBotQuery;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UDataTable* BotTable;

	UFUNCTION()
	void OnSpawnBotQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UCurveFloat* DifficultyCurve;

	//Credit
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	int32 CreditsPerKill;

	//Spawn PickUp
	UPROPERTY(EditDefaultsOnly, Category = "PickUP")
	UEnvQuery* SpawnPickUpQuery;

	UPROPERTY(EditDefaultsOnly, Category = "PickUP")
	TArray<TSubclassOf<AActor>> PickUpClasses;

	UPROPERTY(EditDefaultsOnly, Category = "PickUP")
	float RequiredPickUpDistance;

	UPROPERTY(EditDefaultsOnly, Category = "PickUP")
	int32 DesiredPickUpCount;

	UFUNCTION()
	void OnSpawnPickUpQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	//SaveGame
protected:
	UPROPERTY()
	UCSaveGame* CurrentSaveGame;

	FString SlotName;

public:
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void WriteSaveGame();

	void LoadSaveGame();
};
