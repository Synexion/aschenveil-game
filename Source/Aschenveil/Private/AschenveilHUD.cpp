#include "AschenveilHUD.h"
#include "HealthComponent.h"
#include "Flynn.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Canvas.h"

void AAschenveilHUD::DrawHUD()
{
	Super::DrawHUD();

	UHealthComponent* HC = GetFlynnHealth();
	if (!HC) return;

	float CurrentHP = HC->GetCurrentHealth();
	float MaxHP = HC->GetMaxHealth();
	float Pourcentage = CurrentHP / MaxHP;

	float LargeurMax = 300.0f;
	float Hauteur = 25.0f;
	float X = 50.0f;
	float Y = 50.0f;

	// Fond gris
	DrawRect(FLinearColor(0.2f, 0.2f, 0.2f, 0.8f), X, Y, LargeurMax, Hauteur);

		// Barre Rouge Proportionnelle
	DrawRect(FLinearColor::Red, X, Y, LargeurMax * Pourcentage, Hauteur);
}

UHealthComponent* AAschenveilHUD::GetFlynnHealth() const
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!PC) return nullptr;

	APawn* Pawn = PC->GetPawn();
	if (!Pawn) return nullptr;

	return Pawn->FindComponentByClass<UHealthComponent>();
}