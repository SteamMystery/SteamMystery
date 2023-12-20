// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneCaptureComponent2D.h"
#include "IconSceneCaptureComponent2D.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class STEAMMYSTERY_API UIconSceneCaptureComponent2D : public USceneCaptureComponent2D
{
	GENERATED_BODY()

protected:
	UIconSceneCaptureComponent2D();
	
	virtual void BeginPlay() override;
	
};
