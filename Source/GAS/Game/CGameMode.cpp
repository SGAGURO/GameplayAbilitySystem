#include "CGameMode.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EngineUtils.h"
#include "DrawDebugHelpers.h"
#include "Characters/CBot.h"
#include "Characters/CPlayer.h"
#include "Components/CAttributeComponent.h"
#include "CPlayerState.h"

static TAutoConsoleVariable<bool> CVarSpawnBots(TEXT("SGA.SpawnBots"), false, TEXT("Enable spawning of bots"), ECVF_Cheat);

ACGameMode::ACGameMode()
{
	SpawnTimerInterval = 2.f;
	CreditsPerKill = 20;

	DesiredPickUpCount = 10;
	RequiredPickUpDistance = 2000;

	PlayerStateClass = ACPlayerState::StaticClass();
}

void ACGameMode::StartPlay()
{
	Super::StartPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots, this, &ACGameMode::SpawnBotTimerElapsed, SpawnTimerInterval, true);

	if (ensure(PickUpClasses.Num() > 0))
	{
		UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnPickUpQuery, this, EEnvQueryRunMode::AllMatching, nullptr);
		if (ensure(QueryInstance))
		{
			QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &ACGameMode::OnSpawnPickUpQueryCompleted);
		}
	}
}

void ACGameMode::KillEmAll()
{
	for (TActorIterator<ACBot> It(GetWorld()); It; ++It)
	{
		ACBot* Bot = *It;

		UCAttributeComponent* AttributeComp = UCAttributeComponent::GetAttributes(Bot);
		if (ensure(AttributeComp) && AttributeComp->IsAlive())
		{
			AttributeComp->Kill(this);
		}
	}
}

void ACGameMode::OnActorKilled(AActor* VictimActor, AActor* Killer)
{
	ACPlayer* Player = Cast<ACPlayer>(VictimActor);
	if (Player)
	{
		FTimerHandle TimerHandle_RespawnDelay;
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "RespawnPlayerElapsed", Player->GetController());

		float RespawnDelay = 2.0f;
		GetWorldTimerManager().SetTimer(TimerHandle_RespawnDelay, Delegate, RespawnDelay, false);
	}

	APawn* KillerPawn = Cast<APawn>(Killer);
	if (KillerPawn)
	{
		ACPlayerState* PS = KillerPawn->GetPlayerState<ACPlayerState>();
		if (PS)
		{
			PS->AddCredits(CreditsPerKill);
		}
	}

	UE_LOG(LogTemp, Log, TEXT("OnActorKilled: Victim: %s, Killer: %s"), *GetNameSafe(VictimActor), *GetNameSafe(Killer));
}

void ACGameMode::RespawnPlayerElapsed(AController* Controller)
{
	if (ensure(Controller))
	{
		Controller->UnPossess();

		RestartPlayer(Controller);
	}
}

void ACGameMode::SpawnBotTimerElapsed()
{
	if (!CVarSpawnBots.GetValueOnGameThread())
	{
		//UE_LOG(LogTemp, Warning, TEXT("Bot spawning disabled via cvar 'CVarSpawnBots'."));
		return;
	}

	int32 NrOfAliveBots = 0;
	for (TActorIterator<ACBot> It(GetWorld()); It; ++It)
	{
		ACBot* Bot = *It;

		UCAttributeComponent* AttributeComp = UCAttributeComponent::GetAttributes(Bot);;
		if (ensure(AttributeComp) && AttributeComp->IsAlive())
		{
			NrOfAliveBots++;
		}
	}

	UE_LOG(LogTemp, Log, TEXT("Found %i alive bots."), NrOfAliveBots);

	float MaxBotCount = 10.0f;
	
	if (DifficultyCurve)
	{
		MaxBotCount = DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
	}

	if ((int32)NrOfAliveBots >= MaxBotCount)
	{
		UE_LOG(LogTemp, Log, TEXT("At maximum bot capacity. Skipping bot spawn."));
		return;
	}

	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnBotQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);
	if (ensure(QueryInstance))
	{
		QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &ACGameMode::OnSpawnBotQueryCompleted);
	}
}

void ACGameMode::OnSpawnBotQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{
	if (QueryStatus != EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn bot EQS Query Failed!"));
		return;
	}

	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();
	if (Locations.IsValidIndex(0))
	{
		GetWorld()->SpawnActor<AActor>(BotClass, Locations[0], FRotator::ZeroRotator);
		
		DrawDebugSphere(GetWorld(), Locations[0], 50.0f, 20, FColor::Blue, false, 60.0f);
	}
}

void ACGameMode::OnSpawnPickUpQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{
	//Check query failed
	if (QueryStatus != EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn PickUp EQS Query Failed!"));
		return;
	}

	//Get all Matched item locations
	TArray<FVector> EQSLocations = QueryInstance->GetResultsAsLocations();

	//Already spawend locations
	TArray<FVector> UsedLocations;

	//Iterator for while
	int32 SpawnCounter = 0;

	//Iterator reached end or not enough item count
	while (SpawnCounter < DesiredPickUpCount && EQSLocations.Num() > 0)
	{
		//Get a random item location
		int32 RandomLocationIndex = FMath::RandRange(0, EQSLocations.Num() - 1);
		FVector PickedLocation = EQSLocations[RandomLocationIndex];

		//Remove for next iterator
		EQSLocations.RemoveAt(RandomLocationIndex);

		//Check distance
		bool bValidLocation = true;
		for (FVector OtherLocation : UsedLocations)
		{
			float DistanceTo = (PickedLocation - OtherLocation).Size();

			//Too close
			if (DistanceTo < RequiredPickUpDistance)
			{
				DrawDebugSphere(GetWorld(), PickedLocation, 50.0f, 20, FColor::Red, false, 10.0f);

				bValidLocation = false;
				break;
			}
		}

		//Skip to next iterator because too close
		if (!bValidLocation)
		{
			continue;
		}

		//Get random ClassRef to spawn
		int32 RandomClassIndex = FMath::RandRange(0, PickUpClasses.Num() - 1);
		TSubclassOf<AActor> RandomPowerupClass = PickUpClasses[RandomClassIndex];

		//Actullay spawn
		GetWorld()->SpawnActor<AActor>(RandomPowerupClass, PickedLocation, FRotator::ZeroRotator);

		//marking for `already spawend` locations
		UsedLocations.Add(PickedLocation);
		SpawnCounter++;
	}
}
