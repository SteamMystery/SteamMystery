// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/ItemWidgets/MaterialWidget.h"

#include "Components/TextBlock.h"

void UMaterialWidget::SetMaterial(const FText InName, const int32 InCount, const int32 InNeeded)
{
	Name->SetText(InName);
	Count->SetText(FText::AsNumber(InCount));
	Needed->SetText(FText::AsNumber(InNeeded));
	bIsFullFilled = InCount == InNeeded;
}

bool UMaterialWidget::IsFullFilled() const
{
	return bIsFullFilled;
}
