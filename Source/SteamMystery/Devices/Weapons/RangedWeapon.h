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

	virtual bool Use() const override;

	ARangedWeapon();
protected:
	UPROPERTY(EditAnywhere)
	USceneComponent* FirePoint;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AProjectile>  ProjectileClass;

	UPROPERTY(EditDefaultsOnly)
	class USoundBase* FireSound;
};
