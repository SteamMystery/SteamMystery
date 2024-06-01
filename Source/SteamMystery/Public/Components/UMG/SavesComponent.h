// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWidgetComponent.h"
#include "SavesComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class STEAMMYSTERY_API USavesComponent : public UBaseWidgetComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void ShowAsSaveable(const int32 ZOrder) const;

	virtual void Show(const int32 ZOrder) const override;
};
