#include "CBTService_CheckAttackRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

void UCBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	//Get BBComp
	UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();
	if (ensure(BlackBoardComp))
	{
		//Get TargetActor
		AActor* TargetActor = Cast<AActor>(BlackBoardComp->GetValueAsObject("TargetActor"));
		if (TargetActor)
		{
			//Get AIController
			AAIController* AIC = OwnerComp.GetAIOwner();
			if (ensure(AIC))
			{
				//Get AIPawn
				APawn* AIPawn = AIC->GetPawn();
				if (ensure(AIPawn))
				{
					//Get Distance
					float DistanceTo = FVector::Distance(TargetActor->GetActorLocation(), AIPawn->GetActorLocation());

					//In Range
					bool bInRange = DistanceTo < 2000.f;

					//In Sight
					bool bInSight = false;
					if (bInRange)
					{
						bInSight = AIC->LineOfSightTo(TargetActor);
					}

					//Set BB Value
					BlackBoardComp->SetValueAsBool(AttackRangeKey.SelectedKeyName, (bInRange && bInSight));
				}
			}
		}
	}
}