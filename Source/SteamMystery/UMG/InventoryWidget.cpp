// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"

#include "ItemWidget.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "GameFramework/Character.h"
#include "SteamMystery/Components/InventoryComponent.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (const APlayerController* Controller = GetOwningPlayer())
		if (const ACharacter* Character = Controller->GetCharacter())
			Inventory = Character->GetComponentByClass<UInventoryComponent>();
	Items->ClearChildren();
	if(Inventory)
	{
		Coins->SetText(FText::AsNumber(Inventory->GetCoins()));
		for (const auto Element : Inventory->GetItems())
		{
			const auto Widget = CreateWidget<UItemWidget>(GetOwningPlayer(), ItemWidgetClass);
			Widget->SetItem(Element.Key, Element.Value);
			Widget->SetDescBlock(Description);
			Items->AddChild(Widget);
		}
	}
}
