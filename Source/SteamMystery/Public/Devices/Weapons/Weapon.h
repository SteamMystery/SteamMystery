// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/WeaponItem.h"
#include "SteamMystery/Public/Devices/Device.h"
#include "Weapon.generated.h"


UCLASS()
class STEAMMYSTERY_API AWeapon : public ADevice
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure)
	FWeaponItem GetWeaponStats() const;
};
