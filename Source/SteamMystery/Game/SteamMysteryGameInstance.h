// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SteamMysteryGameInstance.generated.h"

class UGameSave;
class USaveGame;
/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API USteamMysteryGameInstance : public UGameInstance
{
	GENERATED_BODY()

	virtual void Init() override;
public:

	UFUNCTION(BlueprintPure)
	UGameSave* GetSave() const;

	UFUNCTION(BlueprintCallable)
	void SetSave(UGameSave* Value);
private:
	UPROPERTY()
	UGameSave* SaveGame;
	
};
