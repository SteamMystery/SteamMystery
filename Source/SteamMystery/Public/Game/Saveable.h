// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Saveable.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI)
class USaveable : public UInterface
{
	GENERATED_BODY()
	
};

class STEAMMYSTERY_API ISaveable
{
	GENERATED_BODY()

	public:

	UFUNCTION(BlueprintNativeEvent)
	void OnActorLoaded();
	
};
