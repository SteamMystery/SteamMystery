// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquipmentItem.h"
#include "WeaponItem.generated.h"



/**
 * 
 */
USTRUCT()
struct FWeaponItem: public FEquipmentItem
{
	GENERATED_BODY()
	
	FWeaponItem()
	{
		Stats.Emplace(EStat::Damage);
		Stats.Emplace(EStat::Recharge);
		Stats.Emplace(EStat::Range);
	}
};
