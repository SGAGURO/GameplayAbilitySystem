#include "CChest.h"
#include "Net/UnrealNetwork.h"

ACChest::ACChest()
{
	BottomMesh = CreateDefaultSubobject<UStaticMeshComponent>("BottomMesh");
	RootComponent = BottomMesh;

	TopMesh = CreateDefaultSubobject<UStaticMeshComponent>("TopMesh");
	TopMesh->SetupAttachment(BottomMesh);

	TargetPitch = 110;

	SetReplicates(true);
}

void ACChest::Interact_Implementation(APawn* InstigatorPawn)
{
	//Send to client(OnRep_TopOpened fucntion will be called on clients, It's notify)
	bTopOpened = !bTopOpened;

	//Manually trigger on Server
	OnRep_TopOpened();
}

void ACChest::OnRep_TopOpened()
{
	float CurrPitch = bTopOpened ? TargetPitch : 0.0f;
	TopMesh->SetRelativeRotation(FRotator(CurrPitch, 0, 0));
}

void ACChest::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACChest, bTopOpened);
}