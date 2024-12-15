#include "CChest.h"

ACChest::ACChest()
{
	BottomMesh = CreateDefaultSubobject<UStaticMeshComponent>("BottomMesh");
	RootComponent = BottomMesh;

	TopMesh = CreateDefaultSubobject<UStaticMeshComponent>("TopMesh");
	TopMesh->SetupAttachment(BottomMesh);

	TargetPitch = 110;
}

void ACChest::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACChest::Interact_Implementation(APawn* InstigatorPawn)
{
	TopMesh->SetRelativeRotation(FRotator(TargetPitch, 0, 0));
}