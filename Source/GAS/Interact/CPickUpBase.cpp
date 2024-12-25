#include "CPickUpBase.h"
#include "Net/UnrealNetwork.h"
#include "Components/SphereComponent.h"

ACPickUpBase::ACPickUpBase()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("PickUp");
	RootComponent = SphereComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetupAttachment(RootComponent);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RespawnTime = 10.0f;
	bIsActive = true;

	SetReplicates(true);
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
	bIsActive = bActive;	//Server
	OnRep_IsActive();		//Other Clients
}

void ACPickUpBase::OnRep_IsActive()
{
	SetActorEnableCollision(bIsActive);
	RootComponent->SetVisibility(bIsActive, true);
}

void ACPickUpBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACPickUpBase, bIsActive);
}