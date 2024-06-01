// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/ItemWidgets/InventoryWidget.h"

#include "ItemDescriptionWidget.h"
#include "Components/PanelWidget.h"
#include "Game/MainPlayerState.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (const auto Controller = GetOwningPlayer())
		if (const auto Inventory = Controller->GetPlayerState<AMainPlayerState>())
			FillItems(Items, GameInstance->GetItemsDataTable(), Inventory->GetItems(), ItemWidgetClass);
	Sync();
}

void UInventoryWidget::Sync()
{
	Super::Sync();
	for (const auto Element : Items->GetAllChildren())
		if(const auto ItemWidget = Cast<UItemWidget>(Element))
			ItemWidget->OnClicked.AddUniqueDynamic(DescriptionContainer, &UItemDescriptionWidget::SetItem);
}

