// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItemDataAsset.h"
#include "Item.generated.h"

/**
 * 
 */

UCLASS()
class STEAMMYSTERY_API UItem: public UBaseItemDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Price = 0;
};
	
