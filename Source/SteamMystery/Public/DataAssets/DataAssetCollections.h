// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAssetCollections.generated.h"

/**
 * 
 */
UCLASS()
 class STEAMMYSTERY_API UDataAssetCollections : public UPrimaryDataAsset
 {
 	GENERATED_BODY()
 public:

 	UPROPERTY(EditAnywhere, BlueprintReadOnly)
 	TMap<FName, TSubclassOf<class ADevice>> Devices;
 };
