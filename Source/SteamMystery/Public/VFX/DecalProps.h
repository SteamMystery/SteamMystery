// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DecalProps.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FDecalProps
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UMaterialInterface* Material;

	UPROPERTY(EditAnywhere)
	FVector Size;
	
	UPROPERTY(EditAnywhere)
	FRotator Rotation = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere)
	float LifeSpan;

	void SpawnAtHitLocation(const UWorld* InWorld, const FHitResult& HitResult) const;
};