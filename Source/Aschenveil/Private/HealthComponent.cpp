// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...

	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::AppliquerDegats(float DamageAmount) {
	CurrentHealth -= DamageAmount;

	UE_LOG(LogTemp, Warning, TEXT("Degats recus : %f, PV restants : %f"), DamageAmount, CurrentHealth);

	if (CurrentHealth <= 0)
	{
		CurrentHealth = 0;
		UE_LOG(LogTemp, Warning, TEXT("Mort"));
		OnMort.Broadcast();
	}


}

float UHealthComponent::GetCurrentHealth() 
{
	return CurrentHealth;
}

float UHealthComponent::GetMaxHealth()
{
	return MaxHealth;
}