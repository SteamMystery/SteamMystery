// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SteamMystery/Devices/Device.h"
#include "Weapon.generated.h"

UCLASS()
class STEAMMYSTERY_API AWeapon : public ADevice
{
	GENERATED_BODY()
protected:
	
	UPROPERTY(EditAnywhere)
	float Damage = 50.f;
};
