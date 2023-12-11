// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/ItemWidgets/UpgradeDescriptionWidget.h"

#include "Components/Button.h"
#include "Components/ContentWidget.h"
#include "DataAssets/Upgrade.h"
#include "Game/MainPlayerState.h"
#include "UMG/ItemWidgets/MaterialWidget.h"

// ReSharper disable once CppMemberFunctionMayBeConst
void UUpgradeDescriptionWidget::ApplyUpgrade()
{
	if (const auto Row = Item.GetRow<FUpgrade>(GetName()))
	{
		// 	const auto Items = PlayerState->GetItems();
		// for (const auto Element : Row->Materials)
		// 	if(!Items.Contains(Element.Key) || Items[Element.Key] < Element.Value)
		// 		return;
		for (const auto Element : Row->Materials)
			// ReSharper disable once CppExpressionWithoutSideEffects
			PlayerState->RemoveItem(Element.Key, Element.Value);
		OnUpgradeApplied.Broadcast(DeviceName, Item.RowName);
		SetUpgrade(NAME_None, FDataTableRowHandle());
		SyncItem(nullptr);
	}
}

void UUpgradeDescriptionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Button->OnClicked.AddUniqueDynamic(this, &ThisClass::ApplyUpgrade);
	PlayerState = GetOwningPlayerState<AMainPlayerState>();
}

void UUpgradeDescriptionWidget::Sync() const
{
	const auto Row = Item.GetRow<FUpgrade>(GetName());
	Super::SyncItem(Row);
	if (Row)
	{
		Button->SetVisibility(ESlateVisibility::Visible);
		Materials->ClearChildren();
		for (const auto Element : Row->Materials)
			if (const auto Widget = CreateWidget<UMaterialWidget>(GetOwningPlayer(), MaterialWidgetClass))
			{
				Button->SetIsEnabled(true);
				Materials->AddChild(Widget);
				if (PlayerState)
					if (const auto Items = PlayerState->GetItems(); Items.Contains(Element.Key))
					{
						Widget->SetMaterial(FText::FromName(Element.Key), Items[Element.Key], Element.Value);
						if (!Widget->IsFullFilled())
							Button->SetIsEnabled(false);
						continue;
					}
				Widget->SetMaterial(FText::FromName(Element.Key), 0, Element.Value);
				Button->SetIsEnabled(false);
			}
	}
}

void UUpgradeDescriptionWidget::SetUpgrade(const FName InDeviceName, const FDataTableRowHandle& InUpgrade)
{
	DeviceName = InDeviceName;
	SetItem(InUpgrade, 0);
}
