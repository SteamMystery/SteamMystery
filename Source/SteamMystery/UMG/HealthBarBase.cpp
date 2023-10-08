// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBarBase.h"

float UHealthBarBase::GetHealth() const
{
	return Health ? Health->GetPercent() : NULL;
}

void UHealthBarBase::SetHealth(float Value)
{
	if (!Health) return;
	Health->SetPercent(Value);
	Thresholds.KeySort([](const float& A, const float& B)
	{
		return A < B;
	});
	TArray<float> Keys;
	Thresholds.GetKeys(Keys);
	const FLinearColor* Color = nullptr;
	for (const auto Key : Keys)
	{
		if (Key > Value)
		{
			Color = Thresholds.Find(Key);
			break;
		}
	}
	if (!Color)
		Color = new FLinearColor(1.0f, 1.0f, 1.0f);
	Health->SetFillColorAndOpacity(*Color);
}
