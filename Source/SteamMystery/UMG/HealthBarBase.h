// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "HealthBarBase.generated.h"

/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API UHealthBarBase : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* Health;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<float, FLinearColor> Thresholds;
	
	UFUNCTION(BlueprintPure)
	float GetHealth() const;

	UFUNCTION(BlueprintCallable)
	void SetHealth(float Value);
};
