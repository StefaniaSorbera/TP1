// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyLittleProject3Character.h" // Header del propio personaje
#include "Engine/LocalPlayer.h" // Acceso a información del jugador local
#include "Camera/CameraComponent.h" // Componente de cámara
#include "Components/CapsuleComponent.h" // Componente de cápsula para colisiones
#include "GameFramework/CharacterMovementComponent.h" // Movimiento del personaje
#include "GameFramework/SpringArmComponent.h" // Brazo elástico para la cámara
#include "GameFramework/Controller.h" // Controlador de entrada del personaje
#include "EnhancedInputComponent.h" // Nuevo sistema de input mejorado
#include "EnhancedInputSubsystems.h" // Subsistemas del sistema de input
#include "InputActionValue.h" // Valores que reciben las acciones de input
#include "MyLittleProject3.h" // Archivo general del proyecto (logs, defines, etc.)

// Constructor del personaje
AMyLittleProject3Character::AMyLittleProject3Character()
{
	// Inicializa la cápsula de colisión con tamaño ancho = 42, alto = 96
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Configura para que el personaje NO rote con el controlador directamente
	bUseControllerRotationPitch = false; // No rotar en X (inclinación)
	bUseControllerRotationYaw = false;   // No rotar en Y (giro lateral)
	bUseControllerRotationRoll = false;  // No rotar en Z (roll)

	// Configuración del movimiento del personaje
	GetCharacterMovement()->bOrientRotationToMovement = true; // Personaje gira hacia donde se mueve
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // Velocidad de rotación

	// Ajustes adicionales de movimiento
	GetCharacterMovement()->JumpZVelocity = 500.f; // Altura del salto
	GetCharacterMovement()->AirControl = 0.35f; // Control en el aire
	GetCharacterMovement()->MaxWalkSpeed = 500.f; // Velocidad máxima al caminar
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f; // Velocidad mínima al caminar analógicamente
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f; // Frenado al caminar
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f; // Frenado al caer

	// Crear un "Camera Boom" (brazo elástico para alejar la cámara del personaje)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent); // Se adjunta al componente raíz (cápsula de colisión)
	CameraBoom->TargetArmLength = 400.0f; // Distancia de la cámara al personaje
	CameraBoom->bUsePawnControlRotation = true; // Boom usa la rotación del controlador

	// Crear cámara que sigue al personaje
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Se adjunta al final del boom
	FollowCamera->bUsePawnControlRotation = false; // La cámara no rota sola, depende del boom

	// NOTA: El Skeletal Mesh y la AnimBlueprint se asignan desde el Blueprint (no aquí en C++)
}

// Configuración del sistema de entrada
void AMyLittleProject3Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Se castea a EnhancedInputComponent para usar el sistema de input moderno
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{

		// Accion de mostrar mensaje
		EnhancedInputComponent->BindAction(MostrarMensajeAction, ETriggerEvent::Started, this, &AMyLittleProject3Character::DoMostrarMensaje);

		// Accion de mostrar mensaje
		EnhancedInputComponent->BindAction(OcultarAction, ETriggerEvent::Started, this, &AMyLittleProject3Character::DoOcultar);

		// Accion de mostrar mensaje
		EnhancedInputComponent->BindAction(RotarAction, ETriggerEvent::Started, this, &AMyLittleProject3Character::DoRotar);

		// Vincula la acción de salto
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Vincula la acción de movimiento
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyLittleProject3Character::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AMyLittleProject3Character::Look);

		// Vincula la acción de mirar
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyLittleProject3Character::Look);
	}
	else
	{
		// Si no encuentra un EnhancedInputComponent, lanza un error en el log
		UE_LOG(LogMyLittleProject3, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

// Función de movimiento (recibe input 2D del jugador)
void AMyLittleProject3Character::Move(const FInputActionValue& Value)
{
	// Input = vector 2D (ej: WASD o joystick)
	FVector2D MovementVector = Value.Get<FVector2D>();

	// Pasa los valores a DoMove (X = derecha, Y = adelante)
	DoMove(MovementVector.X, MovementVector.Y);
}

// Función de mirar (recibe input 2D del ratón o joystick derecho)
void AMyLittleProject3Character::Look(const FInputActionValue& Value)
{
	// Input = vector 2D (movimiento en ejes X/Y del ratón o joystick)
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// Pasa los valores a DoLook (X = yaw, Y = pitch)
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

// Función que realmente mueve al personaje
void AMyLittleProject3Character::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr) // Solo si existe un controlador
	{
		// Obtiene la rotación del controlador
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0); // Solo se usa el Yaw

		// Calcula vector de dirección hacia adelante
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// Calcula vector de dirección hacia la derecha
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// Aplica movimiento en las direcciones según el input
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

// Función que realmente rota la cámara/personaje
void AMyLittleProject3Character::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		// Añade rotación en yaw (izquierda/derecha) y pitch (arriba/abajo)
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

// Inicia el salto
void AMyLittleProject3Character::DoJumpStart()
{
	Jump();
}

// Termina el salto
void AMyLittleProject3Character::DoJumpEnd()
{
	StopJumping();
}

void AMyLittleProject3Character::DoMostrarMensaje()
{
	// Muestra un mensaje en pantalla
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Turquoise, TEXT("Ola Kent"));

}
void AMyLittleProject3Character::DoOcultar()
{
	// Si el personaje es visible, lo oculta; si está oculto, lo muestra
	bool bIsHidden = IsHidden();
	SetActorHiddenInGame(!bIsHidden);
	SetActorEnableCollision(bIsHidden); // Desactiva colisión si está oculto
	
}
void AMyLittleProject3Character::DoRotar()
{
	// Gira 90 grados en el eje Z cada vez que se llama
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += 90.f;
	SetActorRotation(NewRotation);
	
}


