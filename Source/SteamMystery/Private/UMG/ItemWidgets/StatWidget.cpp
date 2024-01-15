// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/ItemWidgets/StatWidget.h"

#include "Components/TextBlock.h"

void UStatWidget::SetStat(const FText& InName, const float InValue) const
{
	Name->SetText(InName);
	Value->SetText(FText::AsNumber(InValue));
}
