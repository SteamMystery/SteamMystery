// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/ItemWidgets/BaseItemWidget.h"

#include "Components/TextBlock.h"
#include "DataAssets/Item.h"

// void UBaseItemWidget::SetItem(const FItem& Value, const int N)
// {
// 	Item = Value;
// 	ItemCount = N;
// 	Sync();
// }

void UBaseItemWidget::SetItem(const FDataTableRowHandle& Value, const int N)
{
	Item = Value;
	ItemCount = N;
	Sync();
}

FItem UBaseItemWidget::GetItem() const
{
	if (const auto Row = Item.GetRow<FItem>(GetName()))
		return *Row;
	return FItem();
}

void UBaseItemWidget::SyncItem(const FItem* const Row) const
{
	if (Row && !Row->Name.IsNone())
	{
		Name->SetText(FText::FromName(Row->Name));
		Name->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	else
		Name->SetVisibility(ESlateVisibility::Hidden);

	if (ItemCount > 1)
	{
		Count->SetText(FText::AsNumber(ItemCount));
		Count->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	else
		Count->SetVisibility(ESlateVisibility::Hidden);
}

FReply UBaseItemWidget::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	OnClicked.Broadcast(Item, ItemCount);
	return Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);
}

void UBaseItemWidget::Sync() const
{
	SyncItem(Item.GetRow<FItem>(GetName()));
}
