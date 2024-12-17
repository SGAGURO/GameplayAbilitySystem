#include "CPickUpBase.h"

#include "Components/SphereComponent.h"

ACPickUpBase::ACPickUpBase()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("PickUp");
	RootComponent = SphereComp;

	RespawnTime = 10.0f;
}

void ACPickUpBase::Interact_Implementation(APawn* InstigatorPawn)
{
}

void ACPickUpBase::Show()
{
	SetState(true);
}

void ACPickUpBase::HideAndCooldown()
{
	SetState(false);

	GetWorldTimerManager().SetTimer(TimerHandle_RespawnTimer, this, &ACPickUpBase::Show, RespawnTime);
}

void ACPickUpBase::SetState(bool bActive)
{
	SetActorEnableCollision(bActive);
	RootComponent->SetVisibility(bActive, true);
}
