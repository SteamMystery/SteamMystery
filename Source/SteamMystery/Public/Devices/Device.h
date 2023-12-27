// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/EquipmentItem.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "Device.generated.h"

class AMainPlayerState;

UCLASS()
class STEAMMYSTERY_API ADevice : public AActor
{
	GENERATED_BODY()

public:
	ADevice();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool Use();

	UPROPERTY(BlueprintReadWrite)
	bool bIsOnCooldown = false;

	UFUNCTION()
	void Ready();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	FDataTableRowHandle RowHandle;

	UPROPERTY(EditAnywhere)
	UDataTable* UpgradesDataTable;
	
	UPROPERTY()
	AMainPlayerState* PlayerState;
	
	UPROPERTY(EditAnywhere)
	USoundBase* UseSound;
	
public:
	UFUNCTION(BlueprintPure)
	UDataTable* GetUpgradesDataTable() const;
	
	UFUNCTION(BlueprintPure)
	virtual TMap<EStat, float> GetStats() const;
};
