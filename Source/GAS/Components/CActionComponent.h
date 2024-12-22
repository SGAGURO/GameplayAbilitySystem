#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "CActionComponent.generated.h"

class UCAction;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAS_API UCActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCActionComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	bool ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

public:
	//ClassRef parameter to load the 'Action' into memory.
	UFUNCTION(BlueprintCallable, Category = "Actions")
	void AddAction(AActor* Instigator, TSubclassOf<UCAction> ActionClass);

	//it's not just removing a tag, beyond send to GBC.
	UFUNCTION(BlueprintCallable, Category = "Actions")
	void RemoveAction(UCAction* ActionToRemove);

	//Find a specific action via ClassRef
	UFUNCTION(BlueprintCallable, Category = "Actions")
	UCAction* GetAction(TSubclassOf<UCAction> ActionClass) const;

	//When starting 'Action', it is searched using `ActionName`
	UFUNCTION(BlueprintCallable, Category = "Actions")
	bool StartActionByName(AActor* Instigator, FName ActionName);

	//When stopping 'Action', it is searched using `ActionName`
	UFUNCTION(BlueprintCallable, Category = "Actions")
	bool StopActionByName(AActor* Instigator, FName ActionName);

protected:
	UFUNCTION(Server, Reliable)
		void ServerStartAction(AActor* Instigator, FName ActionName);

public:
	//Replaces the 'state'. it's mean currently activating states
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags")
	FGameplayTagContainer ActiveGameplayTags;

protected:
	//A list of actions that are owned by default.
	UPROPERTY(EditAnywhere, Category = "Actions")
	TArray<TSubclassOf<UCAction>> DefaultActions;

	//A list that ObjectRef of Actions created using the `AddAction` method.
	UPROPERTY(Replicated)
	TArray<UCAction*> Actions;
};
