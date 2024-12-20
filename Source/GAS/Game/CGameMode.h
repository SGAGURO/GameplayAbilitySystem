#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "CGameMode.generated.h"

class UEnvQuery;
class UCurveFloat;

UCLASS()
class GAS_API ACGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACGameMode();
	
protected:
	virtual void StartPlay() override;

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

	UFUNCTION()
	void OnSpawnBotQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TSubclassOf<AActor> BotClass;

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
};
