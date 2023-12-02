// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionBarWidget.h"

#include "EquipmentComponent.h"
#include "Components/PanelWidget.h"
#include "GameFramework/Character.h"
#include "UMG/SkillSlotWidget.h"

void UActionBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (const APlayerController* Controller = GetOwningPlayer())
		if (const ACharacter* Character = Controller->GetCharacter())
		{
			EquipmentComponent = Character->GetComponentByClass<UEquipmentComponent>();
			if (EquipmentComponent)
			{
				EquipmentComponent->ActionBarChanged.AddUniqueDynamic(this, &ThisClass::Sync);
				Skills->ClearChildren();
				for (int i = 0; i < EquipmentComponent->ActionBarSize; i++)
					if (const auto Widget = CreateWidget<USkillSlotWidget>(GetOwningPlayer(), SkillSlotWidgetClass))
					{
						Widget->SetItem(EquipmentComponent->GetDeviceAt(i));
						Widget->SetNumber(i);
						Widget->SetKey(EquipmentComponent->GetKeyAt(i));
						Skills->AddChild(Widget);
					}
			}
		}
}

void UActionBarWidget::Sync()
{
	if (EquipmentComponent)
		for (int i = 0; i < EquipmentComponent->ActionBarSize; i++)
			if (const auto Child = Cast<USkillSlotWidget>(Skills->GetChildAt(i)))
				Child->SetItem(EquipmentComponent->GetDeviceAt(i));
}
