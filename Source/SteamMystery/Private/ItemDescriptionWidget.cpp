// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemDescriptionWidget.h"

#include "Components/Button.h"
#include "Components/ContentWidget.h"
#include "Components/TextBlock.h"


void UItemDescriptionWidget::SyncItem(const FItem* Row) const
{
	Super::SyncItem(Row);
	if (Row && !Row->Description.IsEmptyOrWhitespace())
	{
		Description->SetText(Row->Description);
		DescriptionContainer->SetVisibility(ESlateVisibility::Visible);
	}
	else
		DescriptionContainer->SetVisibility(ESlateVisibility::Hidden);
	Count->SetVisibility(ESlateVisibility::Hidden);
	Button->SetVisibility(ESlateVisibility::Hidden);
}
