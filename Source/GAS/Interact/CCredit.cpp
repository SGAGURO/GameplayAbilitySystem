#include "CCredit.h"
#include "Game/CPlayerState.h"

ACCredit::ACCredit()
{
	CreditsAmount = 100;
}

void ACCredit::Interact_Implementation(APawn* InstigatorPawn)
{
	Super::Interact_Implementation(InstigatorPawn);

	if (!ensure(InstigatorPawn))
	{
		return;
	}

	if (ACPlayerState* PS = InstigatorPawn->GetPlayerState<ACPlayerState>())
	{
		PS->AddCredits(CreditsAmount);
		HideAndCooldown();
	}
}