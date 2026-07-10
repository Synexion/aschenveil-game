#include "EnnemiCharacter.h"
#include "HealthComponent.h"
#include "TimerManager.h"
#include "Engine/World.h"

AEnnemiCharacter::AEnnemiCharacter() 
{
	PrimaryActorTick.bCanEverTick = false;
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

void AEnnemiCharacter::BeginPlay()
{
	Super::BeginPlay();

		GetWorldTimerManager().SetTimer(
			TimerAttaque,
			this,
			&AEnnemiCharacter::Attaquer,
			IntervalleAttaque,
			true
		);

		HealthComponent->OnMort.AddDynamic(this, &AEnnemiCharacter::OnMortCallback);
}

void AEnnemiCharacter::Attaquer()
{
	FVector Start = GetActorLocation();
	FVector End = Start + GetActorForwardVector() * 150.0f;
	float Rayon = 50.0f;

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	bool bTouche = GetWorld()->SweepSingleByChannel(
		HitResult, Start, End, FQuat::Identity,
		ECC_Pawn, FCollisionShape::MakeSphere(Rayon), Params
	);

	if (bTouche)
	{
		AActor* Cible = HitResult.GetActor();
		if (Cible)
		{
			UHealthComponent* HealthCible = Cible->FindComponentByClass<UHealthComponent>();
			if (HealthCible)
			{
				HealthCible->AppliquerDegats(DegatsAttaque);
			}
		}
	};
}

void AEnnemiCharacter::OnMortCallback()
{
	GetWorldTimerManager().ClearTimer(TimerAttaque);
	Destroy();
}