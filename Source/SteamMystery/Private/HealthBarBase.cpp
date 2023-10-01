// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBarBase.h"

void UHealthBarBase::SetHealth(float value)
{
	if (!Health) return;
	Health->SetPercent(value);
	Thresholds.KeySort([](const float& A, const float& B)
	{
		return A < B;
	});
	TArray<float> Keys;
	Thresholds.GetKeys(Keys);
	const FLinearColor* Color = nullptr;
	for (const auto Key : Keys)
	{
		if (Key > value)
		{
			Color = Thresholds.Find(Key);
			break;
		}
	}
	if (!Color)
		Color = new FLinearColor(1.0f, 1.0f, 1.0f);
	Health->SetFillColorAndOpacity(*Color);
}
