// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Vfx.generated.h"

class UNiagaraSystem;
/**
 * 
 */
USTRUCT(BlueprintType)
struct FVfx
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* NiagaraSystem;

	UPROPERTY(EditAnywhere)
	UParticleSystem* ParticleSystem;

	UPROPERTY(EditAnywhere)
	FVector Scale = FVector(1);

	void SpawnAtHitLocation(const UWorld* InWorld, const FHitResult& HitResult) const;
	void SpawnAtHitLocation(const UWorld* InWorld, const FHitResult& HitResult, const FVector& InScale) const;
};
