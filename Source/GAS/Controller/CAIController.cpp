#include "CAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void ACAIController::BeginPlay()
{
	Super::BeginPlay();
	
	if (ensureMsgf(BehaviorTree, TEXT("BehaviorTree Asset is nullptr. Did you missing?")))
	{
		RunBehaviorTree(BehaviorTree);
	}

}