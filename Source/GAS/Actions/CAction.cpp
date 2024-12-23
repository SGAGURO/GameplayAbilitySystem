#include "CAction.h"
#include "Components/CActionComponent.h"
#include "Net/UnrealNetwork.h"
#include "GAS.h"

bool UCAction::CanStart_Implementation(AActor* Instigator)
{
	if (IsRunning())
	{
		return false;
	}

	UCActionComponent* Comp = GetOwningComponent();

	if (Comp->ActiveGameplayTags.HasAny(BlockedTags))
	{
		return false;
	}

	return true;
}

void UCAction::StartAction_Implementation(AActor* Instigator)
{
	//UE_LOG(LogTemp, Warning, TEXT("Running: %s"), *GetNameSafe(this));
	LogOnScreen(this, FString::Printf(TEXT("Started: %s"), *ActionName.ToString()), FColor::Green);

	UCActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.AppendTags(GrantsTags);

	RepData.bIsRunning = true;
	RepData.Instigator = Instigator;
}

void UCAction::StopAction_Implementation(AActor* Instigator)
{
	//UE_LOG(LogTemp, Warning, TEXT("Stopped: %s"), *GetNameSafe(this));
	LogOnScreen(this, FString::Printf(TEXT("Stopped: %s"), *ActionName.ToString()), FColor::White);

	//ensureAlways(bIsRunning);
	UCActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.RemoveTags(GrantsTags);

	RepData.bIsRunning = false;
	RepData.Instigator = Instigator;
}

UWorld* UCAction::GetWorld() const
{
	AActor* Actor = Cast<AActor>(GetOuter());
	if (Actor)
	{
		return Actor->GetWorld();
	}

	return nullptr;
}

void UCAction::Initialize(UCActionComponent* NewActionComp)
{
	ActionComp = NewActionComp;
}

UCActionComponent* UCAction::GetOwningComponent() const
{
	return ActionComp;
}

void UCAction::OnRep_RepData()
{
	if (RepData.bIsRunning)
	{
		StartAction(RepData.Instigator);
	}
	else
	{
		StopAction(RepData.Instigator);
	}
}

bool UCAction::IsRunning() const
{
	return RepData.bIsRunning;
}

void UCAction::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCAction, RepData);
	DOREPLIFETIME(UCAction, ActionComp);
}