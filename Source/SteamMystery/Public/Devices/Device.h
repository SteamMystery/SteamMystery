// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/EquipmentItem.h"
#include "Engine/DataTable.h"
#include "Game/MainPlayerController.h"
#include "Game/MainPlayerState.h"
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

	UPROPERTY(EditAnywhere)
	FDataTableRowHandle RowHandle;

	UPROPERTY(EditAnywhere)
	UDataTable* UpgradesDataTable;
	
	UPROPERTY()
	AMainPlayerState* PlayerState;

public:
	UFUNCTION(BlueprintPure)
	UDataTable* GetUpgradesDataTable() const;
	UFUNCTION(BlueprintPure)
	virtual FEquipmentItem GetStats() const;
};
