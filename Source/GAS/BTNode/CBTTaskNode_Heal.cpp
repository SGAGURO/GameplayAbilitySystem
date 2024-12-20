#include "CBTTaskNode_Heal.h"
#include "AIController.h"
#include "Components/CAttributeComponent.h"

EBTNodeResult::Type UCBTTaskNode_Heal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* MyPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (MyPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	UCAttributeComponent* AttributeComp = UCAttributeComponent::GetAttributes(MyPawn);
	if (ensure(AttributeComp))
	{
		AttributeComp->ApplyHealthChange(MyPawn, AttributeComp->GetMaxHealth());
	}

	return EBTNodeResult::Succeeded;
}
