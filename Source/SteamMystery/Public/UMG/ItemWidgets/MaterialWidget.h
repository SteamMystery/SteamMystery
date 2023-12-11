// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MaterialWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API UMaterialWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Name;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Count;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Needed;

	bool bIsFullFilled;

public:
	UFUNCTION(BlueprintCallable)
	void SetMaterial(const FText InName, const int32 InCount, const int32 InNeeded);

	UFUNCTION(BlueprintPure)
	bool IsFullFilled() const;
};
