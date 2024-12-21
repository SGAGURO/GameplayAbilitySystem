#include "CAnimInstance.h"
#include "Components/CActionComponent.h"

void UCAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	AActor* OwningActor = GetOwningActor();
	if (OwningActor)
	{
		ActionComp = Cast<UCActionComponent>(OwningActor->GetComponentByClass(UCActionComponent::StaticClass()));
	}
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (ActionComp)
	{
		bIsSprinting = ActionComp->ActiveGameplayTags.HasTag(SprintingTag);
	}
}