// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "WeaponItem.h"
#include "Templates/Tuple.h"
#include "Upgrade.generated.h"

UENUM()
enum class EUpgradeStatType { Point, Percent };


USTRUCT()
struct FUpgradeValue
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float Value = 0;

	UPROPERTY(EditAnywhere)
	EUpgradeStatType Type = EUpgradeStatType::Percent;
};

/**
 * 
 */

USTRUCT()
struct FUpgrade : public FItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TMap<FName, int> Materials;

	UPROPERTY(EditAnywhere)
	TMap<EStat, FUpgradeValue> UpgradeStats;

	void Apply(FEquipmentItem& InItem);
};

inline void FUpgrade::Apply(FEquipmentItem& InItem)
{
	for (const auto Element : UpgradeStats)
		if (InItem.Stats.Contains(Element.Key))
			switch (auto [Value, Type] = Element.Value; Type)
			{
			case EUpgradeStatType::Point:
				InItem.Stats[Element.Key] += Value;
				break;
			case EUpgradeStatType::Percent:
				InItem.Stats[Element.Key] *= (100 + Value) / 100;
				break;
			}
}