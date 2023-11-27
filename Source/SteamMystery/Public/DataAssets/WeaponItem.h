// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquipmentItem.h"
#include "WeaponItem.generated.h"

/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API UWeaponItem : public UEquipmentItem
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere)
	float Damage = 50.f;
	
	UPROPERTY(EditAnywhere)
	float Range = 50.f;
};
