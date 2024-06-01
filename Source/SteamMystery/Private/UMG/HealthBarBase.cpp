// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/UMG/HealthBarBase.h"
#include "Components/ProgressBar.h"

float UHealthBarBase::GetHealth() const
{
	return Health ? Health->GetPercent() : NULL;
}

void UHealthBarBase::SetHealth(const float Value)
{
	if (!Health) return;
	Health->SetPercent(Value);
	Thresholds.KeySort([](const float& A, const float& B)
	{
		return A < B;
	});
	TArray<float> Keys;
	Thresholds.GetKeys(Keys);
	FLinearColor Color = FLinearColor(1, 1, 1);
	for (const auto Key : Keys)
		if (Key > Value)
		{
			Color = *Thresholds.Find(Key);
			break;
		}
	Health->SetFillColorAndOpacity(Color);
}
