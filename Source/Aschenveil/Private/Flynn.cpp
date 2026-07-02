// Fill out your copyright notice in the Description page of Project Settings.


#include "Flynn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AFlynn::AFlynn()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	
	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	// SpringArm suit la rotation de la camera
	SpringArm->bUsePawnControlRotation = true;

	//Positionnement du springArm par defaut
	SpringArm->TargetArmLength = 180.0f;
	SpringArm->SetRelativeLocation(FVector(0.0f, 18.0f, 70.0f));

	// Flynn ne tourne pas avec la caméra
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	// Flynn s'oriente dans la direction du mouvement
	GetCharacterMovement()->bOrientRotationToMovement = true;

}

// Called when the game starts or when spawned
void AFlynn::BeginPlay()
{
	Super::BeginPlay();
	// Active l'IMC Flynn au démarrage
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(IMC_Flynn, 0);
		}
			
	}
	
}

// Called every frame
void AFlynn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFlynn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Appel de la fonction Deplacer et RotationCamera
	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent)) 
	{
		EIC->BindAction(IA_Deplacement, ETriggerEvent::Triggered, this, &AFlynn::Deplacer);
		EIC->BindAction(IA_Camera, ETriggerEvent::Triggered, this, &AFlynn::RotationCamera);
	}
}

// Fonction Deplacer
void AFlynn::Deplacer(const FInputActionValue& Value) {
	// Récupère la valeur de l'axe
	FVector2D DirectionInput = Value.Get<FVector2D>();
	// Rotation complète de la caméra, tout les axes
	FRotator Rotation = GetControlRotation();
	// Blocage de la rotation sur l'axe horizontale
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	// Transforme la Rotation en Direction via Matrix
	FVector DirectionAvant = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	FVector DirectionDroite = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	// Indique au personnage de bouger
	AddMovementInput(DirectionAvant, DirectionInput.Y);
	AddMovementInput(DirectionDroite, DirectionInput.X);
}

// Fonction RotationCamera
void AFlynn::RotationCamera(const FInputActionValue& Value) {
	// Récupère la valeur de l'axe de la souris
	FVector2D MouseInput = Value.Get<FVector2D>();
	// Rotation gauche-droite , via Yaw ( Yaw = axe X )
	AddControllerYawInput(MouseInput.X);
	// Rotation haut-bas , via Pitch ( Pitch = axe Y )
	AddControllerPitchInput(MouseInput.Y);
}