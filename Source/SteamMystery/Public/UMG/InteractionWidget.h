// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionWidget.generated.h"

/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API UInteractionWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* TextBlock;
public:
	UFUNCTION(BlueprintCallable)
	void SetText(const FText InText) const;
};
