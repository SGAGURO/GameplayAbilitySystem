#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "CAction.generated.h"

class UCActionComponent;

UCLASS(Blueprintable)
class GAS_API UCAction : public UObject
{
	GENERATED_BODY()

public:
	//Simply return a bIsRunning
	UFUNCTION(BlueprintCallable, Category = "Action")
	bool IsRunning() const;

	//Instead of checking for Idle state, we check using GameplayTags.
	//For example, if we try to use the same action repeatedly, or if Blocking Tag is enabled, we will return false.
	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	bool CanStart(AActor* Instigator);

	//generally called when an action is initiated by a key input or an event trigger.
	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void StartAction(AActor* Instigator);

	//some action requires a stop event, such as when a key is "released" or after "time has elapsed".
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Action")
	void StopAction(AActor* Instigator);

	//This class, which inherits from UObject, may not support GetWorld.
	UWorld* GetWorld() const override;

protected:
	//ActionComponent that registered this action.
	UFUNCTION(BlueprintCallable, Category = "Action")
	UCActionComponent* GetOwningComponent() const;

protected:
	//The Tags(states) granted by using this action.
	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTagContainer GrantsTags;

	//The Tags(states) that block the use of this `action`.
	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTagContainer BlockedTags;

	//Flag for this Action continues or not
	bool bIsRunning;
	
public:
	//it's a key, used to identify a specific action
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	FName ActionName;

	//A specific Action must become a `StartAction` immediately after `AddAction`.
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	bool bAutoStart;
};
