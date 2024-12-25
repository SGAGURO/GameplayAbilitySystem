#include "CPlayerState.h"
#include "CSaveGame.h"

int32 ACPlayerState::GetCredits() const
{
	return Credits;
}

void ACPlayerState::AddCredits(int32 Delta)
{
	if (!ensure(Delta >= 0.0f))
	{
		return;
	}

	Credits += Delta;

	OnCreditsChanged.Broadcast(this, Credits, Delta);
}

bool ACPlayerState::RemoveCredits(int32 Delta)
{
	if (!ensure(Delta >= 0.0f))
	{
		return false;
	}

	if (Credits < Delta)
	{
		UE_LOG(LogTemp, Error, TEXT("Not Enough Credit"));
		return false;
	}

	Credits -= Delta;

	OnCreditsChanged.Broadcast(this, Credits, -Delta);

	return true;
}

void ACPlayerState::SavePlayerState_Implementation(UCSaveGame* SaveObject)
{
	if (SaveObject)
	{
		SaveObject->Credits = Credits;
	}
}

void ACPlayerState::LoadPlayerState_Implementation(UCSaveGame* SaveObject)
{
	if (SaveObject)
	{
		Credits = SaveObject->Credits;
	}
}