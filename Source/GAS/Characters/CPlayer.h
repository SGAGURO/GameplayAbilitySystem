#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UCInteractComponent;
class UAnimMontage;
class UCAttributeComponent;
class UCActionComponent;

UCLASS()
class GAS_API ACPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	ACPlayer();

protected:
	virtual void PostInitializeComponents() override;

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	FVector GetPawnViewLocation() const override;

	UFUNCTION(Exec)
	void HealSelf(float Amount = 100);

protected:
	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UCAttributeComponent* OwningComp, float NewHealth, float Delta);

private:
	void MoveForward(float Value);
	void MoveRight(float Value);

	void SprintStart();
	void SprintStop();

	void PrimaryAttack();
	void PrimaryAttack_TimeElapsed();

	void SecondaryAttack();
	void SecondaryAttack_TimeElapsed();

	void ThirdAttack();
	void ThirdAttack_TimeElapsed();

	void StartAttackEffects();
	void SpawnProjectile(TSubclassOf<AActor> ClassToSpawn);

	void PrimaryInteract();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCInteractComponent* InteractComp;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	UCAttributeComponent* AttributeComp;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	UCActionComponent* ActionComp;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> PrimaryProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> SecondaryProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> ThirdProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, Category = "Attack")
	UParticleSystem* MuzzleEffect;

	UPROPERTY(VisibleAnywhere, Category = "Attack")
	FName HandSocketName;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	float AttackAnimDelay;

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	FName TimeToHitParamName;

	FTimerHandle TimerHandle_PrimaryAttack;
	FTimerHandle TimerHandle_SecondaryAttack;
	FTimerHandle TimerHandle_ThirdAttack;
};
