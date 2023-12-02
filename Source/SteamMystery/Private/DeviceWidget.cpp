// Fill out your copyright notice in the Description page of Project Settings.


#include "DeviceWidget.h"

#include "ItemDragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "DataAssets/EquipmentItem.h"
#include "Devices/Device.h"


FReply UDeviceWidget::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);
	return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, DragKey).NativeReply;
}

void UDeviceWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
                                         UDragDropOperation*& OutOperation)
{
	UE_LOG(LogTemp, Warning, TEXT("DND"));
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	if (const auto Widget = CreateWidget<ThisClass>(GetOwningPlayer(), this->GetClass()))
	{
		Widget->SetItem(Item, ItemCount);
		if (const auto DnDOperation = Cast<UItemDragDropOperation>(
			UWidgetBlueprintLibrary::CreateDragDropOperation(UItemDragDropOperation::StaticClass())))
		{
			DnDOperation->DefaultDragVisual = Widget;
			DnDOperation->SetItem(Actor);
			OutOperation = DnDOperation;
		}
	}
}

inline TSubclassOf<ADevice> UDeviceWidget::GetActor() const
{
	return Actor;
}

void UDeviceWidget::SetActor(const TSubclassOf<ADevice> Value)
{
	Actor = Value;
	if (const auto CDO = Actor.GetDefaultObject())
		if (const auto Stats = CDO->GetStats())
			SetItem(Stats, 0);
}
