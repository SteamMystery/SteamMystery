// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API UStatWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetStat(const FText& InName, const float InValue) const;
protected:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Name;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Value;
};
