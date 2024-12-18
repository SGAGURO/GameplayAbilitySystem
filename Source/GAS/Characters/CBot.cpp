#include "CBot.h"
#include "Perception/PawnSensingComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/CAttributeComponent.h"

ACBot::ACBot()
{
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");
	AttributeComp = CreateDefaultSubobject<UCAttributeComponent>("AttributeComp");

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ACBot::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PawnSensingComp->OnSeePawn.AddDynamic(this, &ACBot::OnPawnSeen);
}

void ACBot::OnPawnSeen(APawn* Pawn)
{
	AAIController* AIC = Cast<AAIController>(GetController());
	if (AIC)
	{
		UBlackboardComponent* BBComp = AIC->GetBlackboardComponent();
		BBComp->SetValueAsObject("TargetActor", Pawn);

		DrawDebugString(GetWorld(), GetActorLocation(), "I Found You!", nullptr, FColor::Red, 1.0f, true);
	}
}
