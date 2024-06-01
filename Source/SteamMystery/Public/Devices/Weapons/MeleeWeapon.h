// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "VFX/DecalProps.h"
#include "VFX/Vfx.h"
#include "MeleeWeapon.generated.h"

class UMeleeTraceComponent;
/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API AMeleeWeapon : public AWeapon
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere)
	FVfx HitVfx;
	
	UPROPERTY(EditAnywhere)
	FDecalProps DecalProps;

public:
	
	UFUNCTION()
	void Attack(AActor* HitActor, const FVector& HitLocation);
};
