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

USTRUCT()
struct FActorSaveData
{
	GENERATED_BODY()

	/* Identifier for which Actor this belongs to */
	UPROPERTY()
	FName ActorName;

	/* For movable Actors, keep location,rotation,scale. */
	UPROPERTY()
	FTransform Transform;

	/* Contains all 'SaveGame' marked variables of the Actor */
	UPROPERTY()
	TArray<uint8> ByteData;
};

USTRUCT(BlueprintType)
struct FUpgrades
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FName> Purchased;
	
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

	UPROPERTY()
	TArray<FActorSaveData> SavedActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SaveName;
	
	UPROPERTY()
	FDateTime Time;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName CurrentLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FMapData> MapData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, int32> Items;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, FUpgrades> Upgrades;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, int32> Devices;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> ActionBar;

	UPROPERTY(EditAnywhere)
	int Coins = 0;
};
