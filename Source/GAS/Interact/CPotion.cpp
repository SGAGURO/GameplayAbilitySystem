#include "CPotion.h"
#include "Components/CAttributeComponent.h"
#include "Game/CPlayerState.h"

ACPotion::ACPotion()
{
	CreditCost = 50;
}

void ACPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn))
	{
		return;
	}

	UCAttributeComponent* AttributeComp = UCAttributeComponent::GetAttributes(InstigatorPawn);

	if (ensure(AttributeComp) && !AttributeComp->IsFullHealth())
	{
		if (ACPlayerState* PS = InstigatorPawn->GetPlayerState<ACPlayerState>())
		{
			if (PS->RemoveCredits(CreditCost) && AttributeComp->ApplyHealthChange(this, AttributeComp->GetMaxHealth()))
			{
				HideAndCooldown();
			}
		}
	}
}

#define LOCTEXT_NAMESPACE "Interactable" 
FText ACPotion::GetInteractText_Implementation(APawn* InstigatorPawn)
{
	UCAttributeComponent* AttributeComp = UCAttributeComponent::GetAttributes(InstigatorPawn);
	if (AttributeComp && AttributeComp->IsFullHealth())
	{
		return LOCTEXT("Potion_Warning_FullHealth", "Already at full health.");
	}

	return FText::Format(LOCTEXT("Potion_Message_Interact", "Cost {0} Credits"), CreditCost);
}
#undef LOCTEXT_NAMESPACE