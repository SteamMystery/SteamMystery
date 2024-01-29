// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SteamMystery/Public/Devices/Device.h"
#include "Weapon.generated.h"


UCLASS()
class STEAMMYSTERY_API AWeapon : public ADevice
{
	GENERATED_BODY()
public:

	bool Sweep(FHitResult& HitResult, const FVector& TraceStart, const float Range) const;
	
};
