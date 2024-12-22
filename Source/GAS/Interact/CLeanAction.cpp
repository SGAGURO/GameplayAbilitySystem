#include "CLeanAction.h"
#include "Actions/CAction.h"
#include "Components/CActionComponent.h"

void ACLeanAction::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn && ActionToLearn))
	{
		return;
	}

	UCActionComponent* ActionComp = Cast<UCActionComponent>(InstigatorPawn->GetComponentByClass(UCActionComponent::StaticClass()));
	if (ActionComp)
	{
		if (ActionComp->GetAction(ActionToLearn))
		{
			FString DebugMsg = FString::Printf(TEXT("Action '%s' already learned."), *GetNameSafe(ActionToLearn));
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, DebugMsg);
			return;
		}

		ActionComp->AddAction(InstigatorPawn, ActionToLearn);
		HideAndCooldown();
	}
}