// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BaseGameInstance.generated.h"

class UDataAssetCollections;
class UDataTable;
class UGameSave;
class USaveGame;
/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()

	virtual void Init() override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UDataTable* ItemsDataTable = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UDataTable* UpgradesDataTable = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UDataTable* WeaponsDataTable = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UDataAssetCollections* DataAssetCollections;

public:
	UFUNCTION(BlueprintPure)
	UDataTable* GetItemsDataTable() const;
	
	UFUNCTION(BlueprintPure)
	UDataTable* GetUpgradesDataTable() const;
	
	UFUNCTION(BlueprintPure)
	UDataTable* GetWeaponsDataTable() const;
	
	UFUNCTION(BlueprintPure)
	UDataAssetCollections* GetDataAssetCollections() const;
	virtual void BeginDestroy() override;
};
