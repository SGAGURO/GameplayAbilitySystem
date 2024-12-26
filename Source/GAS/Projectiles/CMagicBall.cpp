#include "CMagicBall.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CAttributeComponent.h"
#include "Components/CActionComponent.h"
#include "Game/CGameplayFunctionLibrary.h"
#include "Actions/CActionEffect.h"

ACMagicBall::ACMagicBall()
{
	SphereComp->SetSphereRadius(20.0f);
	DamageAmount = 20.0f;
	InitialLifeSpan = 10.0f;
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
		UCActionComponent* OtherActionComp = Cast<UCActionComponent>(OtherActor->GetComponentByClass(UCActionComponent::StaticClass()));
		if (OtherActionComp && OtherActionComp->ActiveGameplayTags.HasTag(ReflectTag))
		{
			MoveComp->Velocity = -MoveComp->Velocity;
			SetInstigator(Cast<APawn>(OtherActor));

			return;
		}

		if (UCGameplayFunctionLibrary::ApplyDirectionalDamage(GetInstigator(), OtherActor, DamageAmount, SweepResult))
		{
			Explode();

			if (BurningActionClass && OtherActionComp && HasAuthority())
			{
				OtherActionComp->AddAction(GetInstigator(), BurningActionClass);
			}
		}
	}
}
