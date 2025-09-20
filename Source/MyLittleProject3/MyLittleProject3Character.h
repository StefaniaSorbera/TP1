#pragma once // Evita que este header se incluya múltiples veces

#include "CoreMinimal.h" // Tipos básicos y utilidades de Unreal
#include "GameFramework/Character.h" // Clase base ACharacter (personaje con movimiento y animación)
#include "Logging/LogMacros.h" // Macros para crear logs
#include "MyLittleProject3Character.generated.h" // Necesario para el sistema de reflexión de Unreal

// Declaraciones adelantadas (forward declarations)
class USpringArmComponent; // Brazo elástico de la cámara
class UCameraComponent;    // Componente de cámara
class UInputAction;        // Acción de entrada del sistema Enhanced Input
struct FInputActionValue;  // Valor que reciben las acciones de entrada

// Declaración de una categoría de log para este personaje
DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 *  Personaje jugable en tercera persona
 *  Incluye cámara orbitante controlable por el jugador
 */
UCLASS(abstract) // Clase abstracta (no se puede instanciar directamente en C++, pero sí extender en Blueprint)
class AMyLittleProject3Character : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom que posiciona la cámara detrás del personaje */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Cámara que sigue al personaje */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

protected:

	/** Acción de entrada para saltar */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpAction;

	/** Acción de entrada para moverse */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;

	/** Acción de entrada para mirar (ej: joystick derecho) */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookAction;

	/** Acción de entrada para mirar con el ratón */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MouseLookAction;

	/** Acción de entrada para mostrar mensaje */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MostrarMensajeAction;
	
	/** Acción de entrada para ocultar */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* OcultarAction;

	/** Acción de entrada para rotar */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* RotarAction;


public:

	/** Constructor por defecto */
	AMyLittleProject3Character();

protected:

	/** Configura los bindings de entrada (vincula acciones a funciones) */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	/** Maneja la entrada de movimiento (recibe un vector 2D del input) */
	void Move(const FInputActionValue& Value);

	/** Maneja la entrada de mirar (recibe un vector 2D del input) */
	void Look(const FInputActionValue& Value);

public:

	/** Función BlueprintCallable: mueve al personaje según valores X/Y (derecha/adelante) */
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoMove(float Right, float Forward);

	/** Función BlueprintCallable: rota cámara/personaje según valores de Yaw/Pitch */
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoLook(float Yaw, float Pitch);

	/** Función BlueprintCallable: inicia salto (cuando se presiona el botón de salto) */
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoJumpStart();

	/** Función BlueprintCallable: termina salto (cuando se suelta el botón de salto) */
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoJumpEnd();

	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoMostrarMensaje();

	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoOcultar();

	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoRotar();

public:

	/** Getter para el CameraBoom */
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Getter para la FollowCamera */
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};