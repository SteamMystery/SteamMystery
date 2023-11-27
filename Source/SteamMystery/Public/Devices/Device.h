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
	virtual bool Use();

	UFUNCTION(BlueprintPure)
	FString GetDeviceName() const;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure)
	UStaticMeshComponent* GetMesh() const;

	UPROPERTY(EditAnywhere)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;


	UPROPERTY(EditAnywhere)
	UAnimationAsset* UseAnimation;

	UPROPERTY(BlueprintReadWrite)
	FString DeviceName = "None";

public:
	UFUNCTION(BlueprintPure)
	virtual class UEquipmentItem* GetStats() const
	PURE_VIRTUAL(ADevice::GetStats, return nullptr;)
};
