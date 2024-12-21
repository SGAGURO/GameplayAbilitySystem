#include "CAction.h"

void UCAction::StartAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Warning, TEXT("Running: %s"), *GetNameSafe(this));
}

void UCAction::StopAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Warning, TEXT("Stopped: %s"), *GetNameSafe(this));
}
