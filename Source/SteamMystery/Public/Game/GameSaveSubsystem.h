// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameSaveSubsystem.generated.h"

class UGameSave;
/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSaveLoaded, UGameSave*, GameSave);

UCLASS()
class STEAMMYSTERY_API UGameSaveSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:
	UPROPERTY()
	FOnSaveLoaded OnSaveLoaded;

	UFUNCTION(BlueprintPure)
	UGameSave* GetSave() const;

	void SaveActors() const;
	
	void LoadActors() const;

	UFUNCTION(BlueprintCallable)
	void LoadGame(FString InSlotName);

	UFUNCTION(BlueprintCallable)
	void SaveGame(FString InSlotName) const;

	UFUNCTION(BlueprintCallable)
	void StartNewGame() const;

	UFUNCTION(BlueprintCallable)
	static void ClearSaves();
	
private:
	UPROPERTY()
	UGameSave* CurrentSaveGame;
};
