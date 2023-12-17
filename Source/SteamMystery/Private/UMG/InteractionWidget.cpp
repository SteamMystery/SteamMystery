// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/InteractionWidget.h"

#include "Components/TextBlock.h"

void UInteractionWidget::SetText(const FText InText) const
{
	TextBlock->SetText(InText);
}
