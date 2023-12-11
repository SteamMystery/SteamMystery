// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/ItemWidgets/EquipmentWidget.h"

#include "ItemDescriptionWidget.h"
#include "Components/PanelWidget.h"
#include "Game/MainPlayerState.h"


void UEquipmentWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (const auto Controller = GetOwningPlayer())
		if (const auto Inventory = Controller->GetPlayerState<AMainPlayerState>())
			FillItems(Devices, GameInstance->GetWeaponsDataTable(), Inventory->GetDevices(), DeviceWidgetClass);
	Sync();
}

void UEquipmentWidget::Sync()
{
	Super::Sync();
	for (const auto Element : Devices->GetAllChildren())
		if(const auto ItemWidget = Cast<UItemWidget>(Element))
			ItemWidget->OnClicked.AddUniqueDynamic(DescriptionContainer, &UItemDescriptionWidget::SetItem);
}
