// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class MYLITTLEPROJECT3_API AItem : public AActor
{
		GENERATED_BODY() // Inserta autom�ticamente el c�digo necesario para la reflexi�n y construcci�n
	
public:	
	// Constructor: establece valores por defecto para las propiedades del actor
	AItem();

	// M�todo del ciclo de vida: se llama en cada frame si el Tick est� habilitado
	virtual void Tick(float DeltaTime) override;

	// Propiedad de salud: editable en el editor y en instancias, tipo entero
	UPROPERTY(EditAnywhere)
	int Salud;

	// Propiedad de experiencia: editable solo en el Blueprint/clase, solo lectura en Blueprints
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
	int Experiencia;

	// Propiedad de velocidad: editable en editor e instancias, lectura/escritura en Blueprints
	// Con l�mites de valor y un tooltip en el editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties",
		meta = (ClampMin = "0.0", ClampMax = "100.0", UIMin = "0.0", UIMax = "100.0", ToolTip = "Velocidaditem"))
	float Velocidad;

	// Nombre del �tem: visible en el editor pero no editable, lectura/escritura en Blueprints
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties")
	FString Nombreitem;

	// Tipo del �tem: editable solo en el Blueprint/clase, lectura en Blueprints
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
	FString Tipo;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
