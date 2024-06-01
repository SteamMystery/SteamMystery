// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/ItemWidgets/UpgradeWidget.h"

FReply UUpgradeWidget::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	OnUpgradeClicked.Broadcast(DeviceName, Item);
	return Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);
}

void UUpgradeWidget::SetDeviceName(const FName InDeviceName)
{
	DeviceName = InDeviceName;
}
