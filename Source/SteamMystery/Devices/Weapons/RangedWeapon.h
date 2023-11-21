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

	virtual bool Use() override;
	bool Sweep(FHitResult& HitResult) const;

	ARangedWeapon();
protected:
	
	UPROPERTY(EditAnywhere)
	USceneComponent* FirePoint;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AProjectile>  ProjectileClass;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* FireSound;
	
	UPROPERTY(EditAnywhere)
	float MaxFireDistance;

	UPROPERTY(EditAnywhere)
	float DamageRadius;
	
};
