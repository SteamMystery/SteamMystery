// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/ItemWidgets/ItemCollectionWidget.h"

#include "Components/PanelWidget.h"
#include "Game/BaseGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UItemCollectionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}

void UItemCollectionWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UItemCollectionWidget::Sync()
{
}

void UItemCollectionWidget::FillItems(
	UPanelWidget* PanelWidget,
	const UDataTable* InDataTable,
	TMap<FName, int32> InItems,
	const TSubclassOf<UBaseItemWidget> ItemWidgetClass
) const
{
	PanelWidget->ClearChildren();
	if (ItemWidgetClass && InDataTable)
		for (const auto Element : InItems)
			if (const auto Widget = CreateWidget<UBaseItemWidget>(GetOwningPlayer(), ItemWidgetClass))
			{
				FDataTableRowHandle RowHandle;
				RowHandle.DataTable = InDataTable;
				RowHandle.RowName = Element.Key;
				Widget->SetItem(RowHandle, Element.Value);
				PanelWidget->AddChild(Widget);
			}
}
