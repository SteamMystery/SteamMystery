// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "SteamMystery/Item.h"


void UItemWidget::SetItem(const UItem* Value, const int N)
{
	this->Item = Value;
	Name->SetText(Item->Name);
	Image->SetBrushResourceObject(Item->Icon);
	Count->SetText(FText::AsNumber(N));
}

void UItemWidget::SetDescBlock(UTextBlock* TextBlock)
{
	this->DescriptionTextBlock = TextBlock;
	Button->OnHovered.AddUniqueDynamic(this, &UItemWidget::OnHovered);
	Button->OnUnhovered.AddUniqueDynamic(this, &UItemWidget::OnUnhovered);
}

void UItemWidget::OnHovered()
{
	if(DescriptionTextBlock && Item)
		DescriptionTextBlock->SetText(Item->Description);
}

void UItemWidget::OnUnhovered()
{
	if(DescriptionTextBlock && Item)
		DescriptionTextBlock->SetText(FText::FromString(""));
}


