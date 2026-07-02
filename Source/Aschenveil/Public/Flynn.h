// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Flynn.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class ASCHENVEIL_API AFlynn : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFlynn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;
	UPROPERTY(EditAnywhere)
	UInputMappingContext* IMC_Flynn;
	UPROPERTY(EditAnywhere)
	UInputAction* IA_Deplacement;
	UPROPERTY(EditAnywhere)
	UInputAction* IA_Camera;

	// Fonction

	void Deplacer(const FInputActionValue& Value);
	void RotationCamera(const FInputActionValue& Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
