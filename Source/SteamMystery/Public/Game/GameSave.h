// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GameSave.generated.h"


USTRUCT(BlueprintType)
struct FMapData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName LevelName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> DeadActors;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> PickedItems;
};



/**
 *
 * 
 */
UCLASS()
class STEAMMYSTERY_API UGameSave : public USaveGame
{
	GENERATED_BODY()

public:

	UGameSave();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SaveName;
	
	UPROPERTY()
	FDateTime Time;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName CurrentLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FMapData> MapData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Items;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Upgrades;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Weapons;
};
