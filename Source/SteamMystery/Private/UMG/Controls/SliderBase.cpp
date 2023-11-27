// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/UMG/Controls/SliderBase.h"

#include "Components/ProgressBar.h"
#include "Components/Slider.h"

bool USliderBase::Initialize()
{
	const bool b = Super::Initialize();
	if (Slider)
		Slider->OnValueChanged.AddDynamic(this, &USliderBase::SetValue);
	return b;
}

// ReSharper disable once CppUE4BlueprintCallableFunctionMayBeConst
void USliderBase::SetValue(const float Value)
{
	Slider->SetValue(Value);
	ProgressBar->SetPercent(Value);
	OnValueChanged.Broadcast(Value);
}

float USliderBase::GetValue() const
{
	return Slider->GetValue();
}
