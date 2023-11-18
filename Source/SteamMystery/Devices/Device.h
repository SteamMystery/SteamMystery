// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Device.generated.h"

UCLASS()
class STEAMMYSTERY_API ADevice : public AActor
{
	GENERATED_BODY()
	
public:	
	ADevice();
	
	UFUNCTION(BlueprintCallable)
	virtual bool Use() const;

protected:
	
	UFUNCTION(BlueprintPure)
	UStaticMeshComponent* GetMesh() const;

	UPROPERTY(EditAnywhere)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	float SteamPrice = 0.f;

	UPROPERTY(EditAnywhere)
	float ElectricityPrice = 0.f;
};
