#include "CAttributeComponent.h"

UCAttributeComponent::UCAttributeComponent()
{
	MaxHealth = 100.f;
	Health = MaxHealth;
}


UCAttributeComponent* UCAttributeComponent::GetAttributes(AActor* FromActor)
{
	if (FromActor)
	{
		return Cast<UCAttributeComponent>(FromActor->GetComponentByClass(UCAttributeComponent::StaticClass()));
	}

	return nullptr;
}

bool UCAttributeComponent::ApplyHealthChange(float Delta)
{
	float OldHealth = Health;

	Health = FMath::Clamp(Health + Delta, 0.0f, MaxHealth);

	float ActualDelta = Health - OldHealth;
	OnHealthChanged.Broadcast(nullptr, this, Health, ActualDelta);

	return ActualDelta != 0;
}

bool UCAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

bool UCAttributeComponent::IsFullHealth() const
{
	return Health == MaxHealth;
}

float UCAttributeComponent::GetMaxHealth() const
{
	return MaxHealth;
}
