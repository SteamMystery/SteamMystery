// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SliderBase.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnValueChangedDelegate, float, Value);
/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API USliderBase : public UUserWidget
{
	GENERATED_BODY()

	virtual bool Initialize() override;
public:

	UFUNCTION(BlueprintCallable)
	void SetValue(const float Value);

	UFUNCTION(BlueprintPure)
	float GetValue() const;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnValueChangedDelegate OnValueChanged;
	
protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UProgressBar* ProgressBar;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class USlider* Slider;
};
