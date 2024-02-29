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
	float LifeSpan;
};