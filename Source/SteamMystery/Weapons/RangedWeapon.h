// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "RangedWeapon.generated.h"

class AProjectile;
/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API ARangedWeapon : public AWeapon
{
	GENERATED_BODY()

public:
	ARangedWeapon();
	
	UFUNCTION()
	void Fire();
protected:

	UPROPERTY(EditAnywhere)
	float MaxRange = 1000;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AProjectile>  ProjectileClass;

	UPROPERTY(EditDefaultsOnly)
	FVector ProjectileOffset;
};
