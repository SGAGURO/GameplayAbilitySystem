#include "CMagicBall.h"
#include "Components/SphereComponent.h"
#include "Components/CAttributeComponent.h"
#include "Game/CGameplayFunctionLibrary.h"

ACMagicBall::ACMagicBall()
{
	SphereComp->SetSphereRadius(20.0f);
	DamageAmount = 20.0f;
}

void ACMagicBall::BeginPlay()
{
	Super::BeginPlay();
	
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ACMagicBall::OnActorOverlap);
}

void ACMagicBall::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		if (UCGameplayFunctionLibrary::ApplyDirectionalDamage(GetInstigator(), OtherActor, DamageAmount, SweepResult))
		{
			Explode();
		}
	}
}
