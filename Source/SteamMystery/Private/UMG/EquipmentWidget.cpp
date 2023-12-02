// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/EquipmentWidget.h"

#include "DeviceWidget.h"
#include "EquipmentComponent.h"
#include "Components/PanelWidget.h"
#include "GameFramework/Character.h"

void UEquipmentWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (const APlayerController* Controller = GetOwningPlayer())
		if (const ACharacter* Character = Controller->GetCharacter())
			EquipmentComponent = Character->GetComponentByClass<UEquipmentComponent>();
	Items->ClearChildren();
	if(EquipmentComponent && ItemWidgetClass)
	{
		for (const auto Element : EquipmentComponent->GetItems())
		{
			const auto Widget = CreateWidget<UDeviceWidget>(GetOwningPlayer(), ItemWidgetClass);
			Widget->SetActor(Element);
			Widget->SetDescBlock(Description);
			Items->AddChild(Widget);
		}
	}
}
