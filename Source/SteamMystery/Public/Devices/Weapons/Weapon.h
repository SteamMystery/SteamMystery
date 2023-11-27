// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SteamMystery/Public/DataAssets/WeaponItem.h"
#include "SteamMystery/Public/Devices/Device.h"
#include "Weapon.generated.h"


UCLASS()
class STEAMMYSTERY_API AWeapon : public ADevice
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	UWeaponItem* WeaponStats;
	
public:
	// ReSharper disable once CppHidingFunction
	virtual UWeaponItem* GetStats() const override;
};
