#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CAction.generated.h"

UCLASS(Blueprintable)
class GAS_API UCAction : public UObject
{
	GENERATED_BODY()

public:
	//generally called when an action is initiated by a key input or an event trigger.
	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void StartAction(AActor* Instigator);

	//some action requires a stop event, such as when a key is "released" or after "time has elapsed".
	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void StopAction(AActor* Instigator);
	
public:
	//it's a key, used to identify a specific action
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	FName ActionName;
};
