// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquipmentItem.h"
#include "Item.h"
#include "Templates/Tuple.h"
#include "Upgrade.generated.h"

USTRUCT()
struct FUpgradeValue
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float Value = 0;

	UPROPERTY(EditAnywhere)
	bool Percent = false;
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
	{
		float& Stat = InItem.Stats.FindOrAdd(Element.Key);
		if (auto [Value, Type] = Element.Value; Type)
			Stat *= (100 + Value) / 100;
		else
			Stat += Value;
	}
}
