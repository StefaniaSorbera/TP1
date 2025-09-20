#pragma once // Evita que este header se incluya m�ltiples veces

#include "CoreMinimal.h" // Tipos b�sicos y utilidades de Unreal
#include "GameFramework/Character.h" // Clase base ACharacter (personaje con movimiento y animaci�n)
#include "Logging/LogMacros.h" // Macros para crear logs
#include "MyLittleProject3Character.generated.h" // Necesario para el sistema de reflexi�n de Unreal

// Declaraciones adelantadas (forward declarations)
class USpringArmComponent; // Brazo el�stico de la c�mara
class UCameraComponent;    // Componente de c�mara
class UInputAction;        // Acci�n de entrada del sistema Enhanced Input
struct FInputActionValue;  // Valor que reciben las acciones de entrada

// Declaraci�n de una categor�a de log para este personaje
DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 *  Personaje jugable en tercera persona
 *  Incluye c�mara orbitante controlable por el jugador
 */
UCLASS(abstract) // Clase abstracta (no se puede instanciar directamente en C++, pero s� extender en Blueprint)
class AMyLittleProject3Character : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom que posiciona la c�mara detr�s del personaje */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** C�mara que sigue al personaje */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

protected:

	/** Acci�n de entrada para saltar */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpAction;

	/** Acci�n de entrada para moverse */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;

	/** Acci�n de entrada para mirar (ej: joystick derecho) */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookAction;

	/** Acci�n de entrada para mirar con el rat�n */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MouseLookAction;

	/** Acci�n de entrada para mostrar mensaje */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MostrarMensajeAction;
	
	/** Acci�n de entrada para ocultar */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* OcultarAction;

	/** Acci�n de entrada para rotar */
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

	/** Funci�n BlueprintCallable: mueve al personaje seg�n valores X/Y (derecha/adelante) */
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoMove(float Right, float Forward);

	/** Funci�n BlueprintCallable: rota c�mara/personaje seg�n valores de Yaw/Pitch */
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoLook(float Yaw, float Pitch);

	/** Funci�n BlueprintCallable: inicia salto (cuando se presiona el bot�n de salto) */
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoJumpStart();

	/** Funci�n BlueprintCallable: termina salto (cuando se suelta el bot�n de salto) */
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