#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnnemiCharacter.generated.h"

class UHealthComponent;

UCLASS()
class ASCHENVEIL_API AEnnemiCharacter : public ACharacter {
	GENERATED_BODY()

public:

	AEnnemiCharacter();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float DegatsAttaque = 20.0f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float IntervalleAttaque = 2.0f;

	UFUNCTION()
	void OnMortCallback();

	void Attaquer();


	FTimerHandle TimerAttaque;
};