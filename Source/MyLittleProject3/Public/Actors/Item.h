// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class MYLITTLEPROJECT3_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	int salud;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
	int experiencia;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (ClampMin = "0.0", ClampMax = "100.0", UIMin = "0.0", UIMax = "100.0", ToolTip = "velocidaditem"))
	float velocidad;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties")
	FString nombreitem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
	FString tipo;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
