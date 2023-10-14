// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "MeleeWeapon.generated.h"

/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API AMeleeWeapon : public AWeapon
{
	GENERATED_BODY()

public:
	virtual void Attack() const override;

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditDefaultsOnly)
	float Damage = 50.f;

};
