// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Role.h"
#include "EquipmentItem.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EStat : uint8
{
	None UMETA(DisplayName="None"),
	SteamPrice UMETA(DisplayName="Steam price"),
	ElectricityPrice UMETA(DisplayName="Electricity price"),
	Damage UMETA(DisplayName="Damage"),
	Speed UMETA(DisplayName="Speed"),
	Recharge UMETA(DisplayName="Recharge"),
	Range UMETA(DisplayName="Range"),
	Ammo UMETA(DisplayName="Ammo"),
	ExplosionRadius UMETA(DisplayName="Explosion radius"),
};

USTRUCT()
struct FEquipmentItem : public FItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TMap<EStat, float> Stats;

	UPROPERTY(EditAnywhere)
	TArray<ERole> Roles = {ERole::All};
};
