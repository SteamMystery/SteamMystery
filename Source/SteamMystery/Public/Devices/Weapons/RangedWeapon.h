// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "VFX/Vfx.h"
#include "RangedWeapon.generated.h"

/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API ARangedWeapon : public AWeapon
{
	GENERATED_BODY()

public:
	void Recharge();
	UFUNCTION(BlueprintNativeEvent)
	bool StartRecharge();
	virtual bool Use_Implementation() override;
	

	ARangedWeapon();

	UFUNCTION(BlueprintPure)
	int32 GetCurrentAmmo() const;

	UFUNCTION(BlueprintPure)
	float GetRechargePercent() const;
	
	UFUNCTION(BlueprintPure)
	float GetMaxAmmo() const;
protected:

	int32 Ammo;
	
	bool bIsRecharging;
	
	UPROPERTY(EditAnywhere)
	USceneComponent* FirePoint;

	UPROPERTY(EditDefaultsOnly)
	FVfx MuzzleVfx;

	UPROPERTY(EditAnywhere)
	FName AmmoName;
	
	FTimerHandle RechargeTimer;

	UPROPERTY(EditAnywhere)
	float RadiusScale = 1;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AProjectile> ProjectileClass;
};
