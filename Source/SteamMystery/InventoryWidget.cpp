// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"

#include "InventoryComponent.h"
#include "Item.h"
#include "ItemWidget.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "GameFramework/Character.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (const APlayerController* Controller = GetOwningPlayer())
		if (const ACharacter* Character = Controller->GetCharacter())
			Inventory = Character->GetComponentByClass<UInventoryComponent>();
	if(Inventory)
		for (const TTuple<UItem*, int> Element : Inventory->GetItems())
		{
			const auto Widget = CreateWidget<UItemWidget>(GetOwningPlayer(), ItemWidgetClass);
			Widget->SetItem(Element.Key, Element.Value);
			Widget->SetDescBlock(Description);
			Items->AddChild(Widget);
		}
}