// Fill out your copyright notice in the Description page of Project Settings.


// ReSharper disable CppMemberFunctionMayBeConst
#include <UMG/ItemWidgets/ItemWidget.h>

#include "ItemDragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"
#include <DataAssets/Item.h>

#include "Blueprint/WidgetTree.h"
#include "UMG/DNDWidget.h"


void UItemWidget::SyncItem(const FItem* const Row) const
{
	Super::SyncItem(Row);
	if (Row && Row->Icon)
	{
		Image->SetBrushResourceObject(Row->Icon);
		Image->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	else
		Image->SetVisibility(ESlateVisibility::Hidden);
}

void UItemWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	Sync();
}

FReply UItemWidget::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);
	return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, DragKey).NativeReply;
}

void UItemWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
                                       UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	if (UDNDWidgetClass)
		if (const auto Widget = CreateWidget<UDNDWidget>(GetOwningPlayer(), UDNDWidgetClass))
		{
			const auto ItemStruct = GetItem();
			Widget->SetImage(ItemStruct.Icon);
			if (const auto DnDOperation = Cast<UItemDragDropOperation>(
				UWidgetBlueprintLibrary::CreateDragDropOperation(UItemDragDropOperation::StaticClass())))
			{
				DnDOperation->DefaultDragVisual = Widget;
				DnDOperation->SetItem(ItemStruct.Name);
				OutOperation = DnDOperation;
			}
		}
}
