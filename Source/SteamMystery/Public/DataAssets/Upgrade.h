// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Templates/Tuple.h"
#include "Upgrade.generated.h"

UENUM()
enum class EUpgradeStatType { Point, Percent };

UENUM()
enum class EUpgradeStat { Damage, Recharge };

USTRUCT()
struct FUpgradeValue
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FString Value;

	UPROPERTY(EditAnywhere)
	EUpgradeStatType Type;
};

/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API UUpgrade : public UBaseItemDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	class UEquipmentItem* Item = nullptr;

	UPROPERTY(EditAnywhere)
	TMap<UItem*, int> Materials;

	UPROPERTY(EditAnywhere)
	TMap<EUpgradeStat, FUpgradeValue> UpgradeStats;
};
