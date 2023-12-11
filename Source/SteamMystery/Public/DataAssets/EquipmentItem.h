// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "EquipmentItem.generated.h"

/**
 * 
 */

UENUM()
enum class EStat { None, Damage, Recharge, Range};

USTRUCT()
struct FEquipmentItem : public FItem
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	float SteamPrice = 0.f;

	UPROPERTY(EditAnywhere)
	float ElectricityPrice = 0.f;

	UPROPERTY(EditAnywhere)
	float RechargeTime = 0.f;
	
	UPROPERTY(EditAnywhere)
	TMap<EStat, float> Stats;
};

// UCLASS()
// class STEAMMYSTERY_API UEquipmentItem : public UItem
// {
// 	GENERATED_BODY()
// public:
// 	UPROPERTY(EditAnywhere)
// 	float SteamPrice = 0.f;
//
// 	UPROPERTY(EditAnywhere)
// 	float ElectricityPrice = 0.f;
//
// 	UPROPERTY(EditAnywhere)
// 	float RechargeTime = 0.f;
// };
