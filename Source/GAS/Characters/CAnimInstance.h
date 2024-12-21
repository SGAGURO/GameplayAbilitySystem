#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameplayTagContainer.h"
#include "CAnimInstance.generated.h"

class UCActionComponent;

UCLASS()
class GAS_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	void NativeInitializeAnimation() override;
	void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	UCActionComponent* ActionComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Animation")
	bool bIsSprinting;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
	FGameplayTag SprintingTag;
};
