#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CBot.generated.h"

UCLASS()
class GAS_API ACBot : public ACharacter
{
	GENERATED_BODY()

public:
	ACBot();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
