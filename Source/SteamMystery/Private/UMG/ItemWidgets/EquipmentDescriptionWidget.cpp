// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/ItemWidgets/EquipmentDescriptionWidget.h"

#include "Components/PanelWidget.h"
#include "DataAssets/EquipmentItem.h"
#include "UMG/ItemWidgets/StatWidget.h"

void UEquipmentDescriptionWidget::Sync() const
{
	const auto Row = Item.GetRow<FEquipmentItem>(GetName());
	Super::SyncItem(Row);
	if (Row)
	{
		Stats->ClearChildren();
		for (const auto Element : Row->Stats)
			if (const auto Widget = CreateWidget<UStatWidget>(GetOwningPlayer(), StatWidgetClass))
			{
				Widget->SetStat(UEnum::GetDisplayValueAsText(Element.Key), Element.Value);
				Stats->AddChild(Widget);
			}
	}
}
